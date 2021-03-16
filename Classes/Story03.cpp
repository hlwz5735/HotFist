#include "Story03.h"
#include "SceneFactory.h"

bool Story03::init() {
    if (!Story::init()) {
        return false;
    }
    dialogBox_bottom->setVisible(false);
    dialogBox_top->setVisible(false);
    SpriteFrameCache *frameStart = SpriteFrameCache::getInstance();
    frameStart->addSpriteFramesWithFile("Story00.plist", "Story00.png");
    frameStart->addSpriteFramesWithFile("Story03.plist", "Story03.png");
    count = 1;
    nextEvt();
    return true;
}

void Story03::nextEvt() {
    state = false;
    if (count == 0) {
        state = true;
        count++;
    } else if (count == 1) {
        event01();
        state = true;
        count++;
    } else if (count == 2) {
        clear();
        event02();
        state = true;
        count++;
    } else if (count == 3) {
        clear();
        event03();
        state = true;
        count++;
    } else if (count == 4) {
        clear();
        event04();
        state = true;
        count++;
    } else if (count == 5) {
        clear();
        event05();
        state = true;
        count++;
    } else if (count == 6) {
        clear();
        event06();
        state = true;
        count++;
    } else if (count == 7) {
        clear();
        event07();
        state = true;
        count++;
    } else {
        CCScene *scene = SceneFactory::loadLevel("03");
        _director->replaceScene(TransitionFade::create(1.0f, scene));
    }
}

void Story03::event01() {
    showNormansImage();
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("03_01.png"));
    dialogBox_top->setVisible(true);
}

void Story03::event02() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("03_02.png"));
    dialogBox_bottom->setVisible(true);
}

void Story03::event03() {
    showNormansImage();
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("03_03.png"));
    dialogBox_top->setVisible(true);
}

void Story03::event04() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("03_04.png"));
    dialogBox_bottom->setVisible(true);
}

void Story03::event05() {
    showNormansImage();
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("03_05.png"));
    dialogBox_top->setVisible(true);
}

void Story03::event06() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("03_06.png"));
    dialogBox_bottom->setVisible(true);
}

void Story03::event07() {
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("03_07.png"));
}

void Story03::onEnter()
{
    Layer::onEnter();
    AudioEngine::stopAll();
    AudioEngine::play2d("Audio/01-Story02.mp3", true);
}
