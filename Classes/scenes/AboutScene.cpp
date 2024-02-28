#include "AboutScene.h"
#include "SceneFactory.h"

bool AboutScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto layer = Layer::create();

    Sprite *sptMaker = Sprite::create("makeGroup.png");
    sptMaker->setPosition(Point(sptMaker->getContentSize().width / 2 - 20, sptMaker->getContentSize().height / 2));
    this->addChild(sptMaker);

    MenuItemImage *pReturn = MenuItemImage::create(
        "returnMenu.png",
        "returnMenuSlected.png",
        [this](Ref *r) { this->menuReturnCall(r); });
    pReturn->setOpacity(180);

    Menu *makeMenu = Menu::create(pReturn, nullptr);
    makeMenu->setPosition(Point(Director::getInstance()->getVisibleSize().width - pReturn->getContentSize().width, pReturn->getContentSize().height / 2));

    layer->addChild(makeMenu, 5);
    this->addChild(layer);

    return true;
}

Ref *AboutScene::menuReturnCall(Ref *pSneder)
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.2f, SceneFactory::titleScene()));
    return this;
}