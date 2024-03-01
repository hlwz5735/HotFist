#include "StartScene.h"
#include "SceneFactory.h"

bool StartScene::init() {
    if (!Scene::init()) {
        return false;
    }
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    auto layer = Layer::create();

    SpriteFrameCache *frameStart = SpriteFrameCache::getInstance();
    frameStart->addSpriteFramesWithFile("startpages.plist", "startpages.png");

    Sprite *pStartBg = Sprite::createWithSpriteFrameName("start_back.png");
    pStartBg->setScale(2);
    pStartBg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    layer->addChild(pStartBg, 0);

    /**************************文字效果***********************************/
    Sprite *pLabel0 = Sprite::createWithSpriteFrameName("qi.png");
    pLabel0->setPosition(visibleSize.width, visibleSize.height / 2);
    Sprite *pLabel1 = Sprite::createWithSpriteFrameName("lu.png");
    pLabel1->setPosition(visibleSize.width + pLabel1->getContentSize().width,  visibleSize.height);
    Sprite *pLabel2 = Sprite::createWithSpriteFrameName("ruan.png");
    pLabel2->setPosition(Point(visibleSize.width + pLabel2->getContentSize().width, 0));
    Sprite *pLabel3 = Sprite::createWithSpriteFrameName("jian.png");
    pLabel3->setPosition(Point(0, visibleSize.height));
    Sprite *pLabel4 = Sprite::createWithSpriteFrameName("she.png");
    pLabel4->setPosition(Point(0, 0));
    Sprite *pLabel5 = Sprite::createWithSpriteFrameName("ji.png");
    pLabel5->setPosition(Point(0, visibleSize.height / 2));
    Sprite *pLabel6 = Sprite::createWithSpriteFrameName("da.png");
    pLabel6->setPosition(Point(visibleSize.width / 2, visibleSize.height));
    Sprite *pLabel7 = Sprite::createWithSpriteFrameName("sai.png");
    pLabel7->setPosition(Point(visibleSize.width / 2, 0));

    layer->addChild(pLabel0);
    layer->addChild(pLabel1);
    layer->addChild(pLabel2);
    layer->addChild(pLabel3);
    layer->addChild(pLabel4);
    layer->addChild(pLabel5);
    layer->addChild(pLabel6);
    layer->addChild(pLabel7);

    rotateLabelAction(pLabel0, Point(11 * pLabel0->getContentSize().width / 6, 2 * visibleSize.height / 3));
    rotateLabelAction(pLabel1, Point(17 * pLabel0->getContentSize().width / 6, 2 * visibleSize.height / 3));
    rotateLabelAction(pLabel2, Point(23 * pLabel0->getContentSize().width / 6, 2 * visibleSize.height / 3));
    rotateLabelAction(pLabel3, Point(29 * pLabel0->getContentSize().width / 6, 2 * visibleSize.height / 3));
    rotateLabelAction(pLabel4, Point(35 * pLabel0->getContentSize().width / 6, 2 * visibleSize.height / 3));
    rotateLabelAction(pLabel5, Point(41 * pLabel0->getContentSize().width / 6, 2 * visibleSize.height / 3));
    rotateLabelAction(pLabel6, Point(47 * pLabel0->getContentSize().width / 6, 2 * visibleSize.height / 3));
    rotateLabelAction(pLabel7, Point(53 * pLabel0->getContentSize().width / 6, 2 * visibleSize.height / 3));

    Sprite *pLabelc = Sprite::createWithSpriteFrameName("scan.png");
    pLabelc->setPosition(Point(-4 * pLabelc->getContentSize().width, visibleSize.height / 4));
    Sprite *pLabels = Sprite::createWithSpriteFrameName("ssai.png");
    pLabels->setPosition(Point(-3 * pLabels->getContentSize().width, visibleSize.height / 4));
    Sprite *pLabelz = Sprite::createWithSpriteFrameName("szuo.png");
    pLabelz->setPosition(Point(-2 * pLabelz->getContentSize().width, visibleSize.height / 4));
    Sprite *pLabelp = Sprite::createWithSpriteFrameName("spin.png");
    pLabelp->setPosition(Point(-pLabelp->getContentSize().width, visibleSize.height / 4));

    moveLabelAction(pLabelc, Point(visibleSize.width - 5 * pLabelc->getContentSize().width, visibleSize.height / 4));
    moveLabelAction(pLabels, Point(visibleSize.width - 4 * pLabels->getContentSize().width, visibleSize.height / 4));
    moveLabelAction(pLabelz, Point(visibleSize.width - 3 * pLabelz->getContentSize().width, visibleSize.height / 4));
    moveLabelAction(pLabelp, Point(visibleSize.width - 2 * pLabelp->getContentSize().width, visibleSize.height / 4));

    layer->addChild(pLabelc);
    layer->addChild(pLabels);
    layer->addChild(pLabelz);
    layer->addChild(pLabelp);

    text = Sprite::create("UI_prstoctn.png");
    text->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2.5f));
    text->setVisible(false);
    layer->addChild(text);
    scheduleOnce(AX_SCHEDULE_SELECTOR(StartScene::showTouchToContinueText), 1.5f);

    this->addChild(layer);

    const auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch*, Event*) {
        Director::getInstance()->replaceScene(TransitionFlipX::create(1, SceneFactory::titleScene()));
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

void StartScene::rotateLabelAction(Sprite *pLabel, const Point &pLabelPoint) {
    ActionInterval *pLabelMove = MoveTo::create(1.2f, Vec2(pLabelPoint.x, pLabelPoint.y));
    ActionInterval *pLabelRote = RotateBy::create(1.0f, 360);
    Sequence *pLabelsqc1 = Sequence::create(pLabelMove, pLabelRote, NULL);
    pLabel->runAction(pLabelsqc1);
}

void StartScene::moveLabelAction(Sprite *pLabelMove, const Point &pLabelPointMove) {
    ActionInterval *pLabelMoveTo = MoveTo::create(1.2f, pLabelPointMove);
    pLabelMove->runAction(pLabelMoveTo);
}

void StartScene::showTouchToContinueText(float dt) {
    text->setVisible(true);
}
