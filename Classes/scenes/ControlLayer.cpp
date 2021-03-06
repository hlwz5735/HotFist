#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#include "cocostudio/CCArmature.h"
#include "ControlLayer.h"
#include "ui/CocosGUI.h"
#include "../Readers/GuiReader.h"

USING_NS_CC;
using namespace hotfist;
using cocos2d::ui::Button;

ControlLayer::ControlLayer()
: isLeftBtnPressed(false)
, isRightBtnPressed(false)
{}

bool ControlLayer::init()
{
    if (!Layer::init()) return false;

    const Size visibleSize = _director->getVisibleSize();

    // 资源加载
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UIPacked.plist", "UIPacked.png");
    auto node = GuiReader::readDocument("Config/ui_control_layer.json");
    this->addChild(node);

    this->_bindEventListener(node);

    imageItemSide = Sprite::createWithSpriteFrameName("ImageItemSide.png");
    imageItem = Sprite::createWithSpriteFrameName("ImageNormal.png");
    hp_Bar = Sprite::createWithSpriteFrameName("HP_Bar.png");
    sp_Bar = Sprite::createWithSpriteFrameName("SP_Bar.png");
    tp_Bar = Sprite::createWithSpriteFrameName("TP_Bar.png");

    imageItemSide->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    imageItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    hp_Bar->setAnchorPoint(Point::ZERO);
    sp_Bar->setAnchorPoint(Point::ZERO);
    tp_Bar->setAnchorPoint(Point::ZERO);
    hp_Bar->setPosition(64, 360 - 30);
    sp_Bar->setPosition(64, 360 - 41);
    tp_Bar->setPosition(64, 360 - 53);

    this->addChild(imageItemSide, 20);
    this->addChild(imageItem, 15);
    this->addChild(hp_Bar, 25);
    this->addChild(sp_Bar, 25);
    this->addChild(tp_Bar, 25);

    auto btnPause = Button::create("PauseBtn.png", "PauseBtn_P.png", "", cocos2d::ui::Button::TextureResType::PLIST);
    btnPause->addClickEventListener([this](Ref *sender) {
        this->pauseBtnCallBack(sender);
    });
    btnPause->setPosition(Point(590, 360 - 43));
    this->addChild(btnPause);

    this->scheduleUpdate();

#if DESKTOP_RUNTIME
    this->addKeyEventListener();
#endif

    return true;
}

void ControlLayer::JmpBtnCallBack(Ref *pSender)
{
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING)
    {
        hero->jump();
    }
}

void ControlLayer::AtkBtnCallBack(Ref *pSender)
{
    if (hero->getState() ==Hero:: EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING)
    {
        hero->attack();
    }
}

void ControlLayer::update(float delta)
{
    if (!this->hero) {
        return;
    }
    if (isLeftBtnPressed && !isRightBtnPressed)
    {
        if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING)
        {
            hero->faceto = true;
            //面向翻转
            hero->setDirection(hero->faceto);
            hero->run();
            if (hero->getPositionX() <= 0)
                hero->setPositionX(2);
            hero->initBlock();
        }
    }
    if (!isLeftBtnPressed && isRightBtnPressed)
    {
        if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING)
        {
            hero->faceto = false;
            //面向翻转
            hero->setDirection(hero->faceto);
            hero->run();
            hero->initBlock();
        }
    }

    if (!isLeftBtnPressed && !isRightBtnPressed)
    {
        stopPlayer();
    }

    hp_Bar->setScaleX(hero->HP / 100.0f);
    sp_Bar->setScaleX(hero->SP / 100.0f);
    tp_Bar->setScaleX(hero->TP / 100.0f);

}

void ControlLayer::stopPlayer()
{
    if (hero->getState() == Entity::EntityState::WALKING)
    {
        hero->velocityX = 0;
        if (!hero->inTheAir_flag)
        {
            hero->setState(Entity::EntityState::NORMAL);
            if (hero->getMode() == Hero::HeroMode::LIGHTBLADE)
            {
                hero->m_sprite->getAnimation()->play("SB_Stand");
            } else
                hero->m_sprite->getAnimation()->play("Stand");
        } else
        {
            if (hero->getMode() == Hero::HeroMode::LIGHTBLADE)
            {
                hero->m_sprite->getAnimation()->play("SB_Stand");
            } else
                hero->m_sprite->getAnimation()->play("Stand");
        }
    }
}

void ControlLayer::BladeBtnCallBack(Ref *pSender)
{
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING)
    {
        hero->handBlade();
        imageItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ImageNormal.png"));
    }
}

void ControlLayer::ShieldBtnCallBack(Ref *pSender)
{
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING)
    {
        imageItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ImageNormal.png"));
        hero->modeShield();
    }
}

void ControlLayer::CloakBtnCallBack(Ref *pSender)
{
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING)
    {
        imageItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ImageCloak.png"));
        hero->modeIvisible();
    }
}

void ControlLayer::ClockUPBtnCallBack(Ref *pSender)
{
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING)
    {
        hero->modeClockUp();
        imageItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ImageSpeed.png"));
    }
}

void ControlLayer::pauseBtnCallBack(Ref *pSender)
{
    AudioEngine::pauseAll();
    Director::getInstance()->pushScene(SceneFactory::pauseLayer());
}

void ControlLayer::_bindEventListener(Node *node)
{
    auto button = dynamic_cast<Button*>(node->getChildByName("moveLeftButton"));
    button->addTouchEventListener([this](Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                this->isLeftBtnPressed = true;
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                this->isLeftBtnPressed = false;
                break;
            default:
                break;
        }
    });

    button = dynamic_cast<Button*>(node->getChildByName("moveRightButton"));
    button->addTouchEventListener([this](Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                this->isRightBtnPressed = true;
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                this->isRightBtnPressed = false;
                break;
            default:
                break;
        }
    });

    button = dynamic_cast<Button*>(node->getChildByName("attackButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->AtkBtnCallBack(sender);
    });

    button = dynamic_cast<Button*>(node->getChildByName("jumpButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->JmpBtnCallBack(sender);
    });

    button = dynamic_cast<Button*>(node->getChildByName("shieldButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->ShieldBtnCallBack(sender);
    });

    button = dynamic_cast<Button*>(node->getChildByName("clockUpButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->ClockUPBtnCallBack(sender);
    });

    button = dynamic_cast<Button*>(node->getChildByName("cloakButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->CloakBtnCallBack(sender);
    });

    button = dynamic_cast<Button*>(node->getChildByName("bladeButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->BladeBtnCallBack(sender);
    });
}

#if DESKTOP_RUNTIME
void ControlLayer::addKeyEventListener() {
    typedef EventKeyboard::KeyCode KeyCode;

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        log("Key with keycode %d pressed", keyCode);
        switch (keyCode)
        {
            case KeyCode::KEY_SPACE:
                this->JmpBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_U:
                this->AtkBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_I:
                this->AtkBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_1:
                this->ShieldBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_2:
                this->ClockUPBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_3:
                this->CloakBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_4:
                this->BladeBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_A:
                isLeftBtnPressed = true;
                break;
            case KeyCode::KEY_D:
                isRightBtnPressed = true;
                break;
            default:
                break;
        }
    };
    listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        log("Key with keycode %d released", keyCode);
        switch (keyCode)
        {
            case KeyCode::KEY_A:
                isLeftBtnPressed = false;
                break;
            case KeyCode::KEY_D:
                isRightBtnPressed = false;
                break;
            case KeyCode::KEY_P:
                pauseBtnCallBack(nullptr);
                break;
            default:
                break;
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
#endif
