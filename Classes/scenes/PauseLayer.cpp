#include "PauseLayer.h"
#include "audio/AudioEngine.h"
#include "SceneFactory.h"

USING_NS_CC;

bool PauseLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Sprite *image = Sprite::create("PauseImage.png");
    MenuItemImage *btn = MenuItemImage::create("con_game.png", "con_gameP.png", [this](Ref* pSender) {
        this->btnResume(pSender);
    });
    MenuItemImage *returnTitleBtn = MenuItemImage::create("returnMenu.png", "returnMenuSelected.png", [this](Ref* pSender) {
        _director->replaceScene(SceneFactory::titleScene());
    });
    btn->setPosition(280, 100);
    returnTitleBtn->setPosition(360, 100);
    Menu *pMenu = Menu::create(btn, returnTitleBtn , NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu, 10);
    image->setPosition(Point(320, 160));
    this->addChild(image);
    return true;
}

void PauseLayer::btnResume(Ref *pSender) {
    Director::getInstance()->popScene();
    AudioEngine::resumeAll();
}