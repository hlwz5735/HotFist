#include "Story04.h"
#include "SceneFactory.h"

bool Story04::init() {
    if (!Story::init()) {
        return false;
    }
    dialogBox_bottom->setVisible(false);
    dialogBox_top->setVisible(false);
    SpriteFrameCache *frameStart = SpriteFrameCache::getInstance();
    frameStart->addSpriteFramesWithFile("Story00.plist", "Story00.png");
    frameStart->addSpriteFramesWithFile("Story04.plist", "Story04.png");
    count = 1;
    nextEvt();
    return true;
}

void Story04::nextEvt() {
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
        Scene *scene = SceneFactory::loadLevel("04");
        _director->replaceScene(TransitionFade::create(1.0f, scene));
    }
}

void Story04::event01() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("04_01.png"));
    dialogBox_bottom->setVisible(true);
}

void Story04::event02() {
    showNormansImage();
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("04_02.png"));
    dialogBox_top->setVisible(true);
}

void Story04::event03() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("04_03.png"));
    dialogBox_bottom->setVisible(true);
}

void Story04::event04() {
    showNormansImage();
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("04_04.png"));
    dialogBox_top->setVisible(true);
}

void Story04::event05() {
    showNividasImage();
    text_bottom->setVisible(true);
    text_bottom->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("04_05.png"));
    dialogBox_bottom->setVisible(true);
}

void Story04::event06() {
    showNormansImage();
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("04_06.png"));
    dialogBox_top->setVisible(true);
}

void Story04::event07() {
    text_top->setVisible(true);
    text_top->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("04_07.png"));
}

void Story04::onEnter()
{
    Layer::onEnter();
    AudioEngine::stopAll();
    AudioEngine::play2d("Audio/01-Story02.mp3", true);
}
