#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#include "NewStoryScene.h"
#include "ShowImgCommand.h"
#include "../readers/JsonParser.h"

NewStoryScene::NewStoryScene()
{
    this->eventStep = 0;
    this->eventWaitFrame = 0;
    this->eventCount = 0;
    this->eventWaiting = false;
    this->imgVector = Vector<Sprite *>();
}

bool NewStoryScene::init(const std::string &storyName)
{
    if (!Scene::init())
    {
        return false;
    }

    this->mainLayer = Layer::create();
    this->addChild(mainLayer);

    this->document = getDocumentFromResource(StringUtils::format("Config/story_%s.json", storyName.c_str()));
    this->eventCount = this->document["events"].GetArray().Size();
    this->loadResources();

    this->scheduleUpdate();
    return true;
}

void NewStoryScene::update(float dt)
{
    if (this->eventStep < this->eventCount)
    {
        // 事件执行中，则等待之
        if (this->eventWaitFrame > 0)
        {
            this->eventWaitFrame--;
            return;
        }
        if (this->eventWaiting)
        {
            return;
        }

        auto events = this->document["events"].GetArray();

        this->handleEvent(events[this->eventStep]);

        this->eventStep++;
    }
}

NewStoryScene *NewStoryScene::create(const std::string &storyName)
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

void NewStoryScene::loadResources()
{
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
            }
        }
        else if (type == "mp3")
        {
            AudioEngine::preload(resource["path"].GetString());
        }
    }
}

void NewStoryScene::handleEvent(rapidjson::Value& object)
{
    auto cmdCStr = object["cmd"].GetString();
    const auto cmd = StringUtils::toString(cmdCStr);
    log("当前命令：%s", cmdCStr);
    if (cmd == "playBgm")
    {
        const auto path = object["path"].GetString();
        const bool isLoop = object["loop"].GetBool();

        log("正在播放音乐：[%s][循环：%s]", path, isLoop ? "是" : "否");

        AudioEngine::play2d(path, isLoop);
    }
    else if (cmd == "showImg")
    {
        ShowImgCommand command = ShowImgCommand::fromJsonDocument(object["data"]);

        Sprite *element = dynamic_cast<Sprite*>(this->mainLayer->getChildByName(command.getTag()));
        if (element != nullptr)
        {
            this->mainLayer->removeChild(element, true);
        }
        element = Sprite::createWithSpriteFrameName(command.getTextureName());
        element->setName(command.getTag());

        element->setScale(command.getScaleX(), command.getScaleY());
        element->setFlippedX(command.isFlippedX());
        element->setFlippedY(command.isFlippedY());
        element->setPosition(command.getPosition());
        element->setAnchorPoint(command.getPivot());

        this->mainLayer->addChild(element);
        this->eventWaiting = true;
    }
}
