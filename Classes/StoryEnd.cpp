#include "StoryEnd.h"

bool StoryEnd::init() {
    if (!Story::init()) {
        return false;
    }
    //设置对话框不可见
    dialogBox_bottom->setVisible(false);
    dialogBox_top->setVisible(false);
    SpriteFrameCache *frameStart = SpriteFrameCache::getInstance();
    frameStart->addSpriteFramesWithFile("Story00.plist", "Story00.png");
    frameStart->addSpriteFramesWithFile("StoryEnd.plist", "StoryEnd.png");
    count = 1;
    //由此进入第一个事件
    nextEvt();
    return true;
}

//用了一个相当繁琐的方式，没办法
void StoryEnd::nextEvt() {
    Sprite *sprite1 = Sprite::create();
    sprite1->setAnchorPoint(Point(0, 0));
    sprite1->setPosition(Point(0, 0));
    this->addChild(sprite1);
    FadeIn *fadein = FadeIn::create(1.0f);
    FadeIn *fadein2 = FadeIn::create(0.1f);
    //sprite1->runAction(fadein);
    SpriteFrame *frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_01.png");
    SpriteFrame *frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_02.png");
    SpriteFrame *frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_03.png");
    SpriteFrame *frame4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_04.png");
    SpriteFrame *frame5 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_05.png");
    SpriteFrame *frame6 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_06.png");
    SpriteFrame *frame7 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_07.png");
    SpriteFrame *frame8 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_08.png");
    SpriteFrame *frame9 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_09.png");
    SpriteFrame *frame10 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_10.png");
    SpriteFrame *frame11 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_11.png");
    SpriteFrame *frame12 = SpriteFrameCache::getInstance()->getSpriteFrameByName("end_12.png");
    auto spriteFrameArray = Vector<SpriteFrame *>(12);
    spriteFrameArray.pushBack(frame1);
    spriteFrameArray.pushBack(frame2);
    spriteFrameArray.pushBack(frame3);
    spriteFrameArray.pushBack(frame4);
    spriteFrameArray.pushBack(frame5);
    spriteFrameArray.pushBack(frame6);
    spriteFrameArray.pushBack(frame7);
    spriteFrameArray.pushBack(frame8);
    spriteFrameArray.pushBack(frame9);
    spriteFrameArray.pushBack(frame10);
    spriteFrameArray.pushBack(frame11);
    spriteFrameArray.pushBack(frame12);

    Animation *animation = Animation::createWithSpriteFrames(spriteFrameArray, 4.0f);
    FiniteTimeAction *actionMoveDone = CallFuncN::create(this, callfuncN_selector(StoryEnd::animateFinished));
    sprite1->runAction(Sequence::create(Spawn::createWithTwoActions(fadein, Animate::create(animation)), actionMoveDone, FadeOut::create(2.0f), NULL));
}

void StoryEnd::animateFinished(CCNode *sender) {
    Sprite *text = Sprite::create("StoryImg/end_end.png");
/*	text->setAnchorPoint(Point(0,1344/2));*/
    text->setPosition(Point(320, -1344 / 2));
    this->addChild(text);
    FiniteTimeAction *actionMoveDone = CallFuncN::create(this, callfuncN_selector(StoryEnd::backtoTitle));
    ActionInterval *move = Sequence::create(CCMoveBy::create(40.0f, Point(0, 1344)), DelayTime::create(5.0f), actionMoveDone, NULL);
    text->runAction(move);
}

void StoryEnd::backtoTitle(Node *sender) {
    Scene *gameMenu = SceneFactory::titleScene();
    _director->replaceScene(TransitionFade::create(1.0f, gameMenu));
}

void StoryEnd::onEnter()
{
    Layer::onEnter();
    AudioEngine::stopAll();
    AudioEngine::play2d("Audio/04-Peace.mp3", true);
}
