#include "Story.h"

Story::Story() 
    : count(0)
    , state(false)
{}

bool Story::init() {
    if (!Layer::init()) {
        return false;
    }

    constexpr int b_x = 415, 
        b_y = 50, 
        t_x = 225, 
        t_y = 310;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UIS.plist", "UIS.png");
    dialogBox_bottom = Sprite::createWithSpriteFrameName("UI_dialogBox.png");
    dialogBox_top = Sprite::createWithSpriteFrameName("UI_dialogBox.png");

    dialogBox_bottom->setFlippedX(true);
    dialogBox_bottom->setPosition(Point(b_x, b_y));
    dialogBox_top->setPosition(Point(t_x, t_y));

    crctorImage_bottom = Sprite::create();
    crctorImage_top = Sprite::create();
    text_bottom = Sprite::create();
    text_top = Sprite::create();
    text_bottom->setAnchorPoint(Point(0, 0));
    text_top->setAnchorPoint(Point(0, 0));
    
    const Size visibleSize = Director::getInstance()->getVisibleSize();
    crctorImage_top->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    crctorImage_bottom->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

    this->addChild(dialogBox_top, 5);
    this->addChild(dialogBox_bottom, 5);
    this->addChild(crctorImage_bottom, 10);
    this->addChild(crctorImage_top, 10);
    this->addChild(text_bottom, 15);
    this->addChild(text_top, 15);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        this->nextEvt();
        return true;
    };
      

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Story::clear() {
    dialogBox_bottom->setVisible(false);
    dialogBox_top->setVisible(false);
    text_bottom->setVisible(false);
    text_top->setVisible(false);
    crctorImage_bottom->setVisible(false);
    crctorImage_top->setVisible(false);
}

bool Story::onTouchBegan(Touch *touch, Event *unused_event) {
    if (state) {
        nextEvt();
    }
    return true;
}

void Story::showAmysImage() {
    crctorImage_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amy_Image.png"));
    crctorImage_top->setVisible(true);
}

void Story::showNividasImage() {
    crctorImage_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Nivida_Image.png"));
    crctorImage_bottom->setVisible(true);
}

void Story::showNormansImage() {
    crctorImage_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Norman_Image.png"));
    crctorImage_top->setVisible(true);
}
