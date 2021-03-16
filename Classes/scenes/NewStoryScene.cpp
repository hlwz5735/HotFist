#include <vector>
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#include "cocos2d.h"
#include "../readers/JsonParser.h"
#include "ShowImgCommand.h"
#include "MoveImgCommand.h"
#include "NewStoryScene.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

USING_NS_CC;

NewStoryScene::NewStoryScene()
{
    this->commandStep = 0;
    this->commandWaitFrame = 0;
    this->totalCommandSteps = 0;
    this->isWaitingInput = false;
}

bool NewStoryScene::init(const std::string &storyName)
{
    if (!Scene::init())
    {
        return false;
    }

    this->mainLayer = Layer::create();
    this->addChild(mainLayer);

    // 读取JSON配置文件的数据
    this->document = getDocumentFromResource(StringUtils::format("Config/story_%s.json", storyName.c_str()));
    this->totalCommandSteps = this->document["commands"].GetArray().Size();
    
    // 预加载资源
    this->loadResources();

    // 开启帧更新
    this->scheduleUpdate();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](Touch* t, Event* e) {
        return true;
    };
    listener->onTouchEnded = [this](Touch* t, Event* e) {
        this->isWaitingInput = false;
    };

    _director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, mainLayer);

    return true;
}

NewStoryScene* NewStoryScene::create(const std::string& storyName)
{
    auto pRet = new(std::nothrow) NewStoryScene();
    if (pRet && pRet->init(storyName))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

void NewStoryScene::update(float dt)
{
    // 如果当前事件的步骤计数小于事件总计数
    if (this->commandStep < this->totalCommandSteps)
    {
        // 如果处于等待指令中，则等待之
        if (this->commandWaitFrame > 0)
        {
            this->commandWaitFrame--;
            return;
        }
        // 如果正等待用户输入，则返回
        if (this->isWaitingInput)
        {
            return;
        }

        // 处理当前下标位置的命令
        auto commands = this->document["commands"].GetArray();
        this->handleCommand(commands[this->commandStep]);
        // 命令步骤计数累加
        this->commandStep++;
    }
}


void NewStoryScene::loadResources()
{
    // TODO 当前资源只做了预加载，并没有释放。会导致内存泄露
    auto resources = this->document["resources"].GetArray();
    for (auto it = resources.Begin(); it != resources.End(); it++)
    {
        auto resource = it->GetObject();
        std::string type = resource["type"].GetString();
        if (type == "plist")
        {
            auto fullPath = StringUtils::format("%s.plist", resource["path"].GetString());
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fullPath);
        }
        else if (type == "png")
        {
            auto path = StringUtils::toString(resource["path"].GetString());
            Texture2D *texture = _director->getTextureCache()->addImage(path);
            if (texture)
            {
                Rect rect = Rect::ZERO;
                rect.size = texture->getContentSize();
                auto spriteFrame = SpriteFrame::createWithTexture(texture, rect);
                std::string spriteFrameName = resource["name"].GetString();
                SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, spriteFrameName);
                // 在删除的时候，调用下文，防止内存泄露
                // SpriteFrameCache::getInstance()->removeSpriteFrameByName(spriteFrameName);
            }
        }
        else if (type == "mp3")
        {
            AudioEngine::preload(resource["path"].GetString());
        }
    }
}

/**
 * 事件处理的主入口，首先获取
 */
void NewStoryScene::handleCommand(rapidjson::Value& object)
{
    const auto cmd = StringUtils::toString(object["cmd"].GetString());
    // 播放音乐
    if (cmd == "playBgm")
    {
        const auto path = object["path"].GetString();
        const bool isLoop = object["loop"].GetBool();
        AudioEngine::play2d(path, isLoop);
    }
    // 显示图片
    else if (cmd == "showImg")
    {
        ShowImgCommand command = ShowImgCommand::fromJsonDocument(object["data"]);
        this->handleShowImgCommand(command);
    }
    // 移动图片
    else if (cmd == "moveImg")
    {
        MoveImgCommand command = MoveImgCommand::fromJsonDocument(object["data"]);
        this->handleMoveImgCommand(command);
    }
    // 跳转命令
    else if (cmd == "jump")
    {
        this->commandStep = object["data"]["index"].GetInt();
    }
    else if (cmd == "waitInput")
    {
        this->isWaitingInput = true;
    }
    else if (cmd == "wait")
    {
        this->commandWaitFrame = object["data"]["value"].GetInt();
    }
}

void NewStoryScene::handleShowImgCommand(const ShowImgCommand &cmd)
{
    // 获取当前tag对应的图片是否已存在，如果已存在，则先将其移除
    Sprite* element = dynamic_cast<Sprite*>(this->mainLayer->getChildByName(cmd.getTag()));
    const string& tagName = cmd.getTag();

    if (element != nullptr)
    {
        this->mainLayer->removeChild(element, true);
    }
    element = Sprite::createWithSpriteFrameName(cmd.getTextureName());
    element->setName(cmd.getTag());

    element->setScale(cmd.getScaleX(), cmd.getScaleY());
    element->setFlippedX(cmd.isFlippedX());
    element->setFlippedY(cmd.isFlippedY());
    element->setPosition(cmd.getPosition());
    element->setAnchorPoint(cmd.getPivot());
    element->setOpacity(cmd.getOpacity());

    this->mainLayer->addChild(element);
}

void NewStoryScene::handleMoveImgCommand(const MoveImgCommand& cmd)
{
    // 获取当前tag对应的精灵对象
    Sprite* element = dynamic_cast<Sprite*>(this->mainLayer->getChildByName(cmd.getTag()));
    if (element == nullptr)
    {
        return;
    }

    element->setFlippedX(cmd.getFlippedX());
    element->setFlippedY(cmd.getFlippedY());

    // 计算帧时间到毫秒事件
    constexpr double timePerFrame = 1.0 / 60;
    const float actionTime = timePerFrame * cmd.getDuration();

    Vector<FiniteTimeAction*> actions;
    // 图片移动的设置
    if (cmd.isMoveAbsolute()) {
        if (cmd.getPosition() != element->getPosition())
        {
            actions.pushBack(MoveTo::create(actionTime, cmd.getPosition()));
        }
    }
    else
    {
        if (cmd.getPosition() != Vec2::ZERO)
        {
            actions.pushBack(MoveBy::create(actionTime, cmd.getPosition()));
        }
    }

    if (cmd.getOpacity() != element->getOpacity())
    {
        actions.pushBack(FadeTo::create(actionTime, cmd.getOpacity()));
    }
    if (cmd.getScaleX() != element->getScaleX() || cmd.getScaleY() != element->getScaleY())
    {
        actions.pushBack(ScaleTo::create(actionTime, cmd.getScaleX(), cmd.getScaleY()));
    }

    element->runAction(Spawn::create(actions));
}
