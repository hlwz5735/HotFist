#include "audio/AudioEngine.h"
#include "TitleScene.h"
#include "SceneFactory.h"

USING_NS_AX;

bool TitleScene::init() {
    if (!Scene::init()) {
        return false;
    }
    AudioEngine::preload("Audio/00-Title.mp3");

    auto layer = Layer::create();
    
    const Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // 背景图层有两层，均为静态，如下代码创建之
    Sprite *sp_Background1 = Sprite::create("menu_back.png");
    // sp_Background1->setScale(0.8);
    Sprite *sp_Background2 = Sprite::create("menu_back.png");
    // sp_Background2->setScale(0.8);
    sp_Background1->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    sp_Background2->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

    // 设置层次关系，1在下2在其上
    layer->addChild(sp_Background1, 0);
    layer->addChild(sp_Background2, 1);

    // 创建齐鲁软件设计大赛的Logo精灵：
    Sprite *sp_QiluLogo = Sprite::create("sp_logo.png");
    sp_QiluLogo->setPosition(origin.x + visibleSize.width - sp_QiluLogo->getContentSize().width / 2 + 2,
            visibleSize.height - sp_QiluLogo->getContentSize().height / 2 - 2);
    /*
     * 在此期间创建一个动作，让这个图标一直反复变大变小地蠕动
     */
    auto logoScale = ScaleTo::create(0.4f, 1.12f, 1.12f);
    auto logoScaler = ScaleTo::create(0.4f, 1, 1);
    auto logosqce = Sequence::create(logoScale, logoScaler, NULL);
    auto logoRepeat = RepeatForever::create(logosqce);
    sp_QiluLogo->runAction(logoRepeat);

    layer->addChild(sp_QiluLogo, 5);

    /* 在此处将内四个按钮依次添加了，然后创建一个CCMenu对象把它们括起来显示到图层里面去*/
    // newgame
    MenuItemImage *pNewGame = MenuItemImage::create(
        "new_game.png",
        "new_gameP.png",
        [this](Ref *r) { this->newGmeBtnCallBack(r); });
    // menuIamge的默认坐标原点在屏幕中点
    pNewGame->setPosition(-visibleSize.width / 2 + pNewGame->getContentSize().width,
            -visibleSize.height / 2 + 2.75f * pNewGame->getContentSize().height);
    // continue game
    MenuItemImage *pContGame = MenuItemImage::create(
        "con_game.png",
        "con_gameP.png",
        [this](Ref *r) { this->ctnGmeBtnCallBack(r); });
    pContGame->setPosition(-visibleSize.width / 2 + 4.8f * pContGame->getContentSize().width / 2,
            -visibleSize.height / 2 + 2.75f * pContGame->getContentSize().height);
    // team
    MenuItemImage *pTeamGame = MenuItemImage::create(
        "team_game.png",
        "team_gameP.png",
        [this](Ref *r) { this->tmStudBtnCallBack(r); });
    pTeamGame->setPosition(-visibleSize.width / 2 + pTeamGame->getContentSize().width,
            -visibleSize.height / 2 + 1.2f * pTeamGame->getContentSize().height);
    // quit game
    MenuItemImage *pQuitGame = MenuItemImage::create(
        "quit_game.png",
        "quit_gameP.png",
        [this](Ref *r) { this->quitGmeBtnCallBack(r); });
    pQuitGame->setPosition(-visibleSize.width / 2 + 4.8f * pNewGame->getContentSize().width / 2,
            -visibleSize.height / 2 + 1.2f * pQuitGame->getContentSize().height);

    Menu *pMenuGame = Menu::create(pNewGame, pContGame, pTeamGame, pQuitGame, NULL);
    pMenuGame->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    layer->addChild(pMenuGame, 5);

    this->addChild(layer);
    return true;
};

void TitleScene::onEnter() {
    Scene::onEnter();
    AudioEngine::stopAll();
    AudioEngine::play2d("Audio/00-Title.mp3", true);
}

void TitleScene::onExit()
{
    Node::onExit();
}

// ////////////////按钮的回调函数/////////////////////////////////////
void TitleScene::newGmeBtnCallBack(Ref *pSender) {
    Director::getInstance()->replaceScene(TransitionFade::create(1.2f, SceneFactory::story00()));
}

void TitleScene::ctnGmeBtnCallBack(Ref *pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(1.2f, SceneFactory::ctnLayer()));
}

void TitleScene::tmStudBtnCallBack(Ref *pSender) {
    _director->replaceScene(TransitionFade::create(1.2f, SceneFactory::aboutScene()));
}

void TitleScene::quitGmeBtnCallBack(Ref *pSender) {
    Director::getInstance()->end();
}
