#include "GameLayer.h"
#include "ControlLayer.h"
#include "GameScene.h"

bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    this->gameLayer = GameLayer::create();
    this->controlLayer = ControlLayer::create();

    this->addChild(gameLayer, 0);
    this->addChild(controlLayer, 5);

    return true;
}

void GameScene::loadLevel(const string &levelName)
{
    gameLayer->loadData(cocos2d::StringUtils::format("Levels/level_%s.json", levelName.c_str()));
    controlLayer->hero = gameLayer->getHero();
}
