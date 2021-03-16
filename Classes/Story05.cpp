#include "Story05.h"
#include "SceneFactory.h"

bool Story05::init() {
    if (!Story::init()) {
        return false;
    }
    dialogBox_bottom->setVisible(false);
    dialogBox_top->setVisible(false);
    SpriteFrameCache *frameStart = SpriteFrameCache::getInstance();
    frameStart->addSpriteFramesWithFile("Story00.plist", "Story00.png");
    frameStart->addSpriteFramesWithFile("Story05.plist", "Story05.png");
    count = 1;
    nextEvt();
    return true;
}

void Story05::nextEvt() {
    state = false;
    if (count == 1) {
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
    } else {
        _director->replaceScene(TransitionFade::create(1.0f, SceneFactory::storyEnd()));
    }
}

void Story05::event01() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("05_01.png"));
    dialogBox_bottom->setVisible(true);
}

void Story05::event02() {

}

void Story05::event03() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("05_02.png"));
    dialogBox_bottom->setVisible(true);
}

void Story05::event04() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("05_03.png"));
    dialogBox_bottom->setVisible(true);
}

void Story05::event05() {
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("05_04.png"));
}

void Story05::onEnter()
{
    Layer::onEnter();
    AudioEngine::stopAll();
    AudioEngine::play2d("Audio/01-Story02.mp3", true);
}
