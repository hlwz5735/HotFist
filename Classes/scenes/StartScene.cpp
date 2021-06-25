#include "StartScene.h"
#include "SceneFactory.h"

bool StartScene::init()
{
    if (!Scene::init())
        return false;

    auto layer = Layer::create();

    //Array* stAction = Array::createWithCapacity(12);
    SpriteFrameCache *frameStart = SpriteFrameCache::getInstance();
    frameStart->addSpriteFramesWithFile("startpages.plist", "startpages.png");
    Sprite *pLabel0 = Sprite::createWithSpriteFrameName("qi.png");
    Sprite *pLabel1 = Sprite::createWithSpriteFrameName("lu.png");
    Sprite *pLabel2 = Sprite::createWithSpriteFrameName("ruan.png");
    Sprite *pLabel3 = Sprite::createWithSpriteFrameName("jian.png");
    Sprite *pLabel4 = Sprite::createWithSpriteFrameName("she.png");
    Sprite *pLabel5 = Sprite::createWithSpriteFrameName("ji.png");
    Sprite *pLabel6 = Sprite::createWithSpriteFrameName("da.png");
    Sprite *pLabel7 = Sprite::createWithSpriteFrameName("sai.png");
    Sprite *pLabelc = Sprite::createWithSpriteFrameName("scan.png");
    pLabelc->setPosition(Point(-4 * pLabelc->getContentSize().width, Director::getInstance()->getVisibleSize().height / 4));
    Sprite *pLabels = Sprite::createWithSpriteFrameName("ssai.png");
    pLabels->setPosition(Point(-3 * pLabels->getContentSize().width, Director::getInstance()->getVisibleSize().height / 4));
    Sprite *pLabelz = Sprite::createWithSpriteFrameName("szuo.png");
    pLabelz->setPosition(Point(-2 * pLabelz->getContentSize().width, Director::getInstance()->getVisibleSize().height / 4));
    Sprite *pLabelp = Sprite::createWithSpriteFrameName("spin.png");
    pLabelp->setPosition(Point(-pLabelp->getContentSize().width, Director::getInstance()->getVisibleSize().height / 4));
    Sprite *pStartBg = Sprite::createWithSpriteFrameName("start_back.png");
    pStartBg->setScale(2);
    pStartBg->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2,
            Director::getInstance()->getVisibleSize().height / 2));
    layer->addChild(pStartBg, 0);
    /**************************文字效果***********************************/
    pLabel0->setPosition(Point(Director::getInstance()->getVisibleSize().width,
            Director::getInstance()->getVisibleSize().height / 2));
    layer->addChild(pLabel0);
    Point pLabel0Point = Point(11 * pLabel0->getContentSize().width / 6, 2 * Director::getInstance()->getVisibleSize().height / 3);
    labelAction(pLabel0, pLabel0Point);

    ////////
    pLabel1->setPosition(Point(Director::getInstance()->getVisibleSize().width + pLabel1->getContentSize().width,
            Director::getInstance()->getVisibleSize().height));
    layer->addChild(pLabel1);
    Point pLabel1Point = Point(17 * pLabel0->getContentSize().width / 6, 2 * Director::getInstance()->getVisibleSize().height / 3);
    labelAction(pLabel1, pLabel1Point);

    ///////
    pLabel2->setPosition(Point(Director::getInstance()->getVisibleSize().width + pLabel2->getContentSize().width, 0));
    layer->addChild(pLabel2);
    Point pLabel2Point = Point(23 * pLabel0->getContentSize().width / 6, 2 * Director::getInstance()->getVisibleSize().height / 3);
    labelAction(pLabel2, pLabel2Point);
    ///////
    pLabel3->setPosition(Point(0, Director::getInstance()->getVisibleSize().height));
    layer->addChild(pLabel3);
    Point pLabel3Point = Point(29 * pLabel0->getContentSize().width / 6, 2 * Director::getInstance()->getVisibleSize().height / 3);
    labelAction(pLabel3, pLabel3Point);
    /////////
    pLabel4->setPosition(Point(0, 0));
    layer->addChild(pLabel4);
    Point pLabel4Point = Point(35 * pLabel0->getContentSize().width / 6, 2 * Director::getInstance()->getVisibleSize().height / 3);
    labelAction(pLabel4, pLabel4Point);
    /////////
    pLabel5->setPosition(Point(0, Director::getInstance()->getVisibleSize().height / 2));
    layer->addChild(pLabel5);
    Point pLabel5Point = Point(41 * pLabel0->getContentSize().width / 6, 2 * Director::getInstance()->getVisibleSize().height / 3);
    labelAction(pLabel5, pLabel5Point);
    //Sequence* startAction = Sequence::create(pLabel0,pLabel1,pLabel2,pLabel3,pLabel4,pLabel5,NULL);
    pLabel6->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height));
    layer->addChild(pLabel6);
    Point pLabel6Point = Point(47 * pLabel0->getContentSize().width / 6, 2 * Director::getInstance()->getVisibleSize().height / 3);
    labelAction(pLabel6, pLabel6Point);
    pLabel7->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, 0));
    Point pLabel7Point = Point(53 * pLabel0->getContentSize().width / 6, 2 * Director::getInstance()->getVisibleSize().height / 3);
    layer->addChild(pLabel7);
    labelAction(pLabel7, pLabel7Point);
    Point pLabelcPoint = Point(Director::getInstance()->getVisibleSize().width - 5 * pLabelc->getContentSize().width,
            Director::getInstance()->getVisibleSize().height / 4);
    Point pLabelsPoint = Point(Director::getInstance()->getVisibleSize().width - 4 * pLabels->getContentSize().width,
            Director::getInstance()->getVisibleSize().height / 4);
    Point pLabelzPoint = Point(Director::getInstance()->getVisibleSize().width - 3 * pLabelz->getContentSize().width,
            Director::getInstance()->getVisibleSize().height / 4);
    Point pLabelpPoint = Point(Director::getInstance()->getVisibleSize().width - 2 * pLabelp->getContentSize().width,
            Director::getInstance()->getVisibleSize().height / 4);
    labelActionMoveTo(pLabelc, pLabelcPoint);
    labelActionMoveTo(pLabels, pLabelsPoint);
    labelActionMoveTo(pLabelz, pLabelzPoint);
    labelActionMoveTo(pLabelp, pLabelpPoint);
    layer->addChild(pLabelc);
    layer->addChild(pLabels);
    layer->addChild(pLabelz);
    layer->addChild(pLabelp);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    text = Sprite::create("UI_prstoctn.png");
    text->setColor(ccc3(120, 120, 120));
    text->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2.5f));
    text->setVisible(false);
    layer->addChild(text);

    this->addChild(layer);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    scheduleOnce(schedule_selector(StartScene::labelonStage), 1.5f);
    return true;
}

bool StartScene::onTouchBegan(Touch *touch, Event *pEvent)
{
    CCLOG("%f,%f", Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
    this->toTitleScene();
    return true;
}

void StartScene::toTitleScene()
{
    Director::getInstance()->replaceScene(TransitionFlipX::create(1, SceneFactory::titleScene()));
}

Scene *StartScene::createScene()
{
    return StartScene::create();
}

//动态文字函数实现
void StartScene::labelAction(Sprite *pLabel, Point pLabelPoint)
{
    ActionInterval *pLabelMove = MoveTo::create(1.2f, Vec2(pLabelPoint.x, pLabelPoint.y));
    ActionInterval *pLabelRote = RotateBy::create(1.0f, 360);
    Sequence *pLabelsqc1 = Sequence::create(pLabelMove, pLabelRote, NULL);
    pLabel->runAction(pLabelsqc1);
}

void StartScene::labelActionMoveTo(Sprite *pLabelMove, Point pLabelPointMove)
{
    ActionInterval *pLabelMoveTo = MoveTo::create(1.2f, Vec2(pLabelPointMove.x, pLabelPointMove.y));
    pLabelMove->runAction(pLabelMoveTo);
}

void StartScene::labelonStage(float dt)
{
    text->setVisible(true);
}
