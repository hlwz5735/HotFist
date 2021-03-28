#include <vector>
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#include "cocos2d.h"
#include "../readers/JsonParser.h"
#include "Global.h"
#include "SceneFactory.h"
#include "ShowImgCommand.h"
#include "MoveImgCommand.h"
#include "ShowMsgCommand.h"
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
    this->mainLayer = nullptr;
}

bool NewStoryScene::initWithStoryName(const std::string& storyName)
{
    if (!Scene::init())
    {
        return false;
    }

    const auto visibleSize = _director->getVisibleSize();
    this->mainLayer = Layer::create();
    // 初始化消息对话框
    this->_initMessageDialog();
    this->addChild(mainLayer);

    // 读取JSON配置文件的数据
    this->document = getDocumentFromResource(StringUtils::format("Config/story_%s.json", storyName.c_str()));
    this->totalCommandSteps = this->document["commands"].GetArray().Size();

    // 预加载资源
    this->loadResources();

    // 开启帧更新
    this->scheduleUpdate();

    // 添加当前场景的全局触摸监听，在收到用户的触摸后，更新等待用户输入状态
    auto* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](Touch* t, Event* e)
    {
        return true;
    };
    listener->onTouchEnded = [this](Touch* t, Event* e)
    {
        this->isWaitingInput = false;
    };

    _director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, mainLayer);

    return true;
}

NewStoryScene* NewStoryScene::create(const std::string& storyName)
{
    auto* pRet = new(std::nothrow) NewStoryScene();
    if (pRet && pRet->initWithStoryName(storyName))
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
    while (this->commandStep < this->totalCommandSteps)
    {
        // 读取命令数组
        // TODO 理论上不用每帧都读取一次，应该初始化时读取并解序列化为对象，后续直接使用
        auto commands = this->document["commands"].GetArray();

        // 如果正等待用户输入，则返回
        if (this->isWaitingInput)
        {
            return;
        }
        // 如果处于等待指令中，则等待之
        if (this->commandWaitFrame > 0)
        {
            this->commandWaitFrame--;
            return;
        }

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
            Texture2D* texture = _director->getTextureCache()->addImage(path);
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
        const std::string path = object["path"].GetString();
        const bool isLoop = object["loop"].GetBool();
        AudioEngine::play2d(path, isLoop);
    }
        // 显示图片
    else if (cmd == "showImg")
    {
        const auto command = ShowImgCommand::fromJsonDocument(object["data"]);
        this->handleShowImgCommand(command);
    }
        // 移动图片
    else if (cmd == "moveImg")
    {
        const auto command = MoveImgCommand::fromJsonDocument(object["data"]);
        this->handleMoveImgCommand(command);
    }
        // 跳转命令
    else if (cmd == "jump")
    {
        this->commandStep = object["data"]["index"].GetInt();
    }
        // 等待用户输入
    else if (cmd == "waitInput")
    {
        this->isWaitingInput = true;
    }
        // 等待若干帧
    else if (cmd == "wait")
    {
        this->commandWaitFrame = object["data"]["value"].GetInt();
    }
        // 加载关卡
    else if (cmd == "loadLevel")
    {
        Director::getInstance()->replaceScene(SceneFactory::loadLevel(object["data"]["value"].GetString()));
    }
    else if (cmd == "showMsg")
    {
        const auto command = ShowMsgCommand::fromJsonDocument(object["data"]);
        this->handleShowMsgCommand(command);
    }
    else if (cmd == "hideMsg")
    {
        std::string position = "all";
        if (object.HasMember("value") && object["value"].HasMember("position"))
        {
            position = StringUtils::toString(object["value"]["position"].GetString());
        }
        if (position == "all" || position == "top")
        {
            this->topMessageDialog->setVisible(false);
        }
        if (position == "all" || position == "bottom")
        {
            this->bottomMessageDialog->setVisible(false);
        }
    }
    else
    {
        CCLOG("未知命令：%s", cmd.c_str());
    }
}

void NewStoryScene::handleShowImgCommand(const ShowImgCommand& cmd) const
{
    // 获取当前tag对应的图片是否已存在，如果已存在，则先将其移除
    auto* element = dynamic_cast<Sprite*>(this->mainLayer->getChildByName(cmd.getTag()));
    if (element != nullptr)
    {
        this->mainLayer->removeChild(element, true);
    }

    element = Sprite::createWithSpriteFrameName(cmd.getTextureName());
    element->setName(cmd.getTag());
    element->setAnchorPoint(cmd.getPivot());
    element->setPosition(cmd.getPosition());
    element->setScale(cmd.getScaleX(), cmd.getScaleY());
    element->setFlippedX(cmd.isFlippedX());
    element->setFlippedY(cmd.isFlippedY());
    element->setOpacity(cmd.getOpacity());
    element->setVisible(cmd.isVisible());
    if (cmd.getZIndex() == 0)
    {
        this->mainLayer->addChild(element);
    }
    else
    {
        this->mainLayer->addChild(element, cmd.getZIndex());
    }
}

void NewStoryScene::handleMoveImgCommand(const MoveImgCommand& cmd) const
{
    // 获取当前tag对应的精灵对象
    auto* element = dynamic_cast<Sprite*>(this->mainLayer->getChildByName(cmd.getTag()));
    if (element == nullptr)
    {
        return;
    }
    // 设置精灵的可见性，如果内容不可见，则不执行动作
    element->setVisible(cmd.isVisible());
    if (!cmd.isVisible())
    {
        return;
    }

    element->setFlippedX(cmd.getFlippedX());
    element->setFlippedY(cmd.getFlippedY());


    // 计算帧时间到毫秒事件
    constexpr auto timePerFrame = 1.0 / 60;
    const auto actionTime = static_cast<float>(timePerFrame * cmd.getDuration());

    auto actions = Vector<FiniteTimeAction*>();
    // 图片移动的设置
    if (cmd.isMoveAbsolute())
    {
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

void NewStoryScene::handleShowMsgCommand(const ShowMsgCommand& cmd)
{
    Sprite* avatar, * dialog;
    Label* label;

    if (cmd.getPosition() == "top")
    {
        dialog = this->topMessageDialog;
        avatar = this->topAvatar;
        label = this->topMessageLabel;
    }
    else
    {
        dialog = this->bottomMessageDialog;
        avatar = this->bottomAvatar;
        label = this->bottomMessageLabel;
    }

    label->setString(cmd.getText());
    dialog->setVisible(true);

    if (!cmd.getAvatar().empty())
    {
        avatar->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(cmd.getAvatar()));
    }

    if (cmd.isWaitInput())
    {
        this->isWaitingInput = true;
    }
}



void NewStoryScene::_initMessageDialog()
{
    const auto visibleSize = _director->getVisibleSize();
	constexpr int bx = 415, by = 50,
			tx = 225, ty = 310;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UIS.plist", "UIS.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("avatars.plist", "UIS.png");
	this->topMessageDialog = Sprite::createWithSpriteFrameName("UI_dialogBox.png");
	this->topMessageDialog->setAnchorPoint(Vec2::ZERO);
	this->topMessageDialog->setPosition(0, visibleSize.height - this->topMessageDialog->getContentSize().height);
	this->topMessageDialog->setVisible(false);
	this->mainLayer->addChild(topMessageDialog, 5);
	
	this->bottomMessageDialog = Sprite::createWithSpriteFrameName("UI_dialogBox.png");
	this->bottomMessageDialog->setFlippedX(true);
	this->bottomMessageDialog->setAnchorPoint(Vec2::ZERO);
	this->bottomMessageDialog->setPosition(visibleSize.width - bottomMessageDialog->getContentSize().width, 0);
	this->bottomMessageDialog->setVisible(false);
	this->mainLayer->addChild(bottomMessageDialog, 5);
	
	this->topAvatar = Sprite::create();
	this->topAvatar->setPosition(40, 52);
	this->topMessageDialog->addChild(this->topAvatar);
	
	this->bottomAvatar = Sprite::create();
	this->bottomAvatar->setPosition(346, 50);
	this->bottomMessageDialog->addChild(bottomAvatar);
	
	this->topMessageLabel = _createMessageLabel();
	this->topMessageLabel->setPosition(80, 74);
	this->topMessageDialog->addChild(topMessageLabel);

	this->bottomMessageLabel = _createMessageLabel();
	this->bottomMessageLabel->setPosition(8, 74);
	this->bottomMessageDialog->addChild(bottomMessageLabel);
}

Label* NewStoryScene::_createMessageLabel()
{
    const static TTFConfig ttfConfig("fonts/Deng.ttf", 14 * SCALE_FACTOR, GlyphCollection::DYNAMIC, nullptr, true);
    auto label = Label::createWithTTF(ttfConfig, "");
    label->setLineSpacing(2 * SCALE_FACTOR);
    label->setDimensions(295 * SCALE_FACTOR, 64 * SCALE_FACTOR);
    label->enableOutline(Color4B::BLACK, static_cast<int>(SCALE_FACTOR));
    label->setAnchorPoint(Vec2(0, 1));
    label->setScale(1 / SCALE_FACTOR);
    return label;
}