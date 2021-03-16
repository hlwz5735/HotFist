#include "GameOverLayer.h"
#include "SceneFactory.h"

USING_NS_CC;

bool GameOverLayer::init()
{
    if (!Layer::init())
        return false;
    //创建背景图片精灵
    int randNum = rand() % 4;
    if (randNum == 0)
    {
        sp_Background = Sprite::create("endSprite0.png");
        sp_Background->setScale(0.7f);
    } else if (randNum == 1)
    {
        sp_Background = Sprite::create("endSprite1.png");
        sp_Background->setScale(0.5f);
    } else if (randNum == 2)
    {
        sp_Background = Sprite::create("endSprite2.png");
        sp_Background->setScale(0.5f);
    } else
    {
        sp_Background = Sprite::create("endSprite3.png");
        sp_Background->setScale(0.5f);
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    sp_Background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(sp_Background);

    this->scheduleOnce([this](float delta) {
        this->_director->replaceScene(TransitionFade::create(1.2f, SceneFactory::titleScene()));
    }, 9, "backToTitle");

    return true;
}

Scene *GameOverLayer::Scene()
{
    auto pScene = Scene::create();
    GameOverLayer *pLayer = GameOverLayer::create();
    pScene->addChild(pLayer);
    return pScene;
}

void GameOverLayer::retryBtnCallBack(Ref *pSender)
{
    Director::getInstance()->replaceScene(SceneFactory::titleScene());
}