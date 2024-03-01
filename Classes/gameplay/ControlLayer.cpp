#include "audio/AudioEngine.h"
#include "cocostudio/Armature.h"
#include "ControlLayer.h"

#include "InputManager.h"
#include "SceneFactory.h"
#include "ui/CocosGUI.h"
#include "../readers/GuiReader.h"

USING_NS_AX;
using namespace hotfist;
using ui::Button;
using ui::Widget;

static void addButtonActionListener(Button *btn, const std::function<void ()>& keyDownCallback, const std::function<void ()>& keyUpCallback);
static void addButtonActionForKey(Button *btn, int keyCode);

ControlLayer::ControlLayer(): hero(nullptr),
                              imageItemSide(nullptr),
                              imageItem(nullptr),
                              hp_Bar(nullptr),
                              sp_Bar(nullptr),
                              tp_Bar(nullptr) {
}

bool ControlLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    const Size visibleSize = _director->getVisibleSize();

    // 资源加载
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UIPacked.plist", "UIPacked.png");
    auto node = GuiReader::readDocument("Config/ui_control_layer.json");
    this->addChild(node);

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

    const auto btnPause = Button::create(
        "PauseBtn.png",
        "PauseBtn_P.png",
        "",
        Button::TextureResType::PLIST);
    btnPause->addClickEventListener([this](Ref *sender) { this->pauseBtnCallBack(sender); });
    btnPause->setPosition(Point(590, 360 - 43));
    this->addChild(btnPause);

    this->scheduleUpdate();

    this->bindEventListener(node);
#if DESKTOP_RUNTIME
    this->addKeyEventListener();
#endif

    return true;
}

void ControlLayer::jmpBtnCallBack(Ref *pSender) {
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING) {
        hero->jump();
    }
}

void ControlLayer::atkBtnCallBack(Ref *pSender) {
    if (hero->getState() == Hero::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING) {
        hero->attack();
    }
}

void ControlLayer::update(float delta) {
    hp_Bar->setScaleX(hero->getHp() / 100.0f);
    sp_Bar->setScaleX(hero->getSp() / 100.0f);
    tp_Bar->setScaleX(hero->getTp() / 100.0f);
}

void ControlLayer::bladeBtnCallBack(Ref *pSender) {
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING) {
        hero->handBlade();
        imageItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ImageNormal.png"));
    }
}

void ControlLayer::shieldBtnCallBack(Ref *pSender) {
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING) {
        imageItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ImageNormal.png"));
        hero->modeShield();
    }
}

void ControlLayer::cloakBtnCallBack(Ref *pSender) {
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING) {
        imageItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ImageCloak.png"));
        hero->modeIvisible();
    }
}

void ControlLayer::clockUPBtnCallBack(Ref *pSender) {
    if (hero->getState() == Entity::EntityState::NORMAL || hero->getState() == Entity::EntityState::WALKING) {
        hero->modeClockUp();
        imageItem->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ImageSpeed.png"));
    }
}

void ControlLayer::pauseBtnCallBack(Ref *pSender) {
    AudioEngine::pauseAll();
    Director::getInstance()->pushScene(SceneFactory::pauseLayer());
}

void ControlLayer::bindEventListener(Node *node) {
    auto button = dynamic_cast<Button *>(node->getChildByName("moveLeftButton"));
    addButtonActionForKey(button, InputManager::Keys::DPAD_LEFT);

    button = dynamic_cast<Button *>(node->getChildByName("moveRightButton"));
    addButtonActionForKey(button, InputManager::Keys::DPAD_RIGHT);

    button = dynamic_cast<Button *>(node->getChildByName("attackButton"));
    addButtonActionForKey(button, InputManager::Keys::BTN_ATTACK);

    button = dynamic_cast<Button *>(node->getChildByName("jumpButton"));
    addButtonActionForKey(button, InputManager::Keys::BTN_JUMP);


    button = dynamic_cast<Button *>(node->getChildByName("shieldButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->shieldBtnCallBack(sender);
    });

    button = dynamic_cast<Button *>(node->getChildByName("clockUpButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->clockUPBtnCallBack(sender);
    });

    button = dynamic_cast<Button *>(node->getChildByName("cloakButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->cloakBtnCallBack(sender);
    });

    button = dynamic_cast<Button *>(node->getChildByName("bladeButton"));
    button->addClickEventListener([this](Ref *sender) {
        this->bladeBtnCallBack(sender);
    });
}

void addButtonActionListener(Button *btn, const std::function<void ()>& keyDownCallback, const std::function<void ()>& keyUpCallback) {
    btn->addTouchEventListener([=](Ref *_, Widget::TouchEventType type) {
        switch (type) {
            case Widget::TouchEventType::BEGAN:
                keyDownCallback();
                break;
            case Widget::TouchEventType::ENDED:
            case Widget::TouchEventType::CANCELED:
                keyUpCallback();
                break;
            default:
                break;
        }
    });
}

void addButtonActionForKey(Button *btn, int keyCode) {
    addButtonActionListener(btn, [keyCode] {
        InputManager::getInstance()->setKeyStatus(keyCode, true);
    }, [keyCode] {
        InputManager::getInstance()->setKeyStatus(keyCode, false);
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
                this->jmpBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_U:
                this->atkBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_I:
                this->atkBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_1:
                this->shieldBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_2:
                this->clockUPBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_3:
                this->cloakBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_4:
                this->bladeBtnCallBack(nullptr);
                break;
            case KeyCode::KEY_A:
                InputManager::getInstance()->setKeyStatus(InputManager::DPAD_LEFT, true);
                break;
            case KeyCode::KEY_D:
                InputManager::getInstance()->setKeyStatus(InputManager::DPAD_RIGHT, true);
                break;
            default:
                break;
        }
    };
    listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        log("Key with keycode %d released", keyCode);
        switch (keyCode) {
            case KeyCode::KEY_A:
                InputManager::getInstance()->setKeyStatus(InputManager::DPAD_LEFT, false);
                break;
            case KeyCode::KEY_D:
                InputManager::getInstance()->setKeyStatus(InputManager::DPAD_RIGHT, false);
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
