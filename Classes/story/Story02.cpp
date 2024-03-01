#include "Story02.h"
#include "../SceneFactory.h"

bool Story02::init() {
    if (!Story::init()) {
        return false;
    }
    dialogBox_bottom->setVisible(false);
    dialogBox_top->setVisible(false);
    auto frameStart = SpriteFrameCache::getInstance();
    frameStart->addSpriteFramesWithFile("Story00.plist", "Story00.png");
    frameStart->addSpriteFramesWithFile("Story02.plist", "Story02.png");
    count = 1;
    nextEvt();
    return true;
}

void Story02::nextEvt() {
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
    } else {
        _director->replaceScene(TransitionFade::create(1.0f, SceneFactory::loadLevel("02")));
    }
}

void Story02::event01() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("02_01.png"));
    dialogBox_bottom->setVisible(true);
}

void Story02::event02() {
    showAmysImage();
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("02_02.png"));
    dialogBox_top->setVisible(true);
}

void Story02::event03() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("02_03.png"));
    dialogBox_bottom->setVisible(true);
}

void Story02::event04() {
    showAmysImage();
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("02_04.png"));
    dialogBox_top->setVisible(true);
}

void Story02::event05() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("02_05.png"));
    dialogBox_bottom->setVisible(true);
}

void Story02::event06() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("02_06.png"));
    dialogBox_bottom->setVisible(true);
}

void Story02::onEnter()
{
    Layer::onEnter();
    AudioEngine::stopAll();
    AudioEngine::play2d("Audio/02-Story02.mp3", true);
}
