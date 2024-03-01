#include "SceneFactory.h"

#include "scenes/TitleScene.h"
#include "scenes/GameOverLayer.h"
#include "scenes/GameScene.h"
#include "scenes/AboutScene.h"
#include "scenes/StartScene.h"
#include "scenes/PauseLayer.h"
#include "scenes/TableViewTestLayer.h"

#include "story/Story00.h"
#include "story/Story01.h"
#include "story/Story02.h"
#include "story/Story03.h"
#include "story/Story04.h"
#include "story/Story05.h"
#include "story/StoryEnd.h"

Scene *SceneFactory::story00() {
    return Story00::createScene();
}

Scene *SceneFactory::story01() {
    return Story01::createScene();
}

Scene *SceneFactory::story02() {
    Scene *scene = Scene::create();
    Story02 *storyLayer = Story02::create();
    scene->addChild(storyLayer, 0);
    return scene;
}

Scene *SceneFactory::story03() {
    Scene *scene = Scene::create();
    Story03 *storyLayer = Story03::create();
    scene->addChild(storyLayer, 0);
    return scene;
}

Scene *SceneFactory::story04() {
    Scene *scene = Scene::create();
    Story04 *storyLayer = Story04::create();
    scene->addChild(storyLayer, 0);
    return scene;
}

Scene *SceneFactory::story05() {
    Scene *scene = Scene::create();
    Story05 *storyLayer = Story05::create();
    scene->addChild(storyLayer, 0);
    return scene;
}

Scene *SceneFactory::storyEnd() {
    Scene *scene = Scene::create();
    StoryEnd *storyLayer = StoryEnd::create();
    scene->addChild(storyLayer, 0);
    return scene;
}

Scene *SceneFactory::loadLevel(const std::string &levelName) {
    GameScene *scene = GameScene::create();
    scene->loadLevel(levelName);
    return scene;
}

Scene *SceneFactory::titleScene() {
    return TitleScene::create();
}

Scene *SceneFactory::aboutScene() {
    return AboutScene::create();
}

Scene *SceneFactory::gameOverScene() {
    auto pScene = Scene::create();
    GameOverLayer *layer = GameOverLayer::create();
    pScene->addChild(layer);
    return pScene;
}

Scene *SceneFactory::pauseLayer() {
    Scene *pMenuScene = Scene::create();
    PauseLayer *pMenuLayer = PauseLayer::create();
    pMenuScene->addChild(pMenuLayer);
    return pMenuScene;
}

Scene *SceneFactory::ctnLayer() {
    Scene *pMenuScene = Scene::create();
    TableViewTestLayer *pMenuLayer = TableViewTestLayer::create();
    pMenuScene->addChild(pMenuLayer);
    return pMenuScene;
}

Scene *SceneFactory::startScene() {
    return StartScene::create();
}
