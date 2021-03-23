//
// Created by 厉猛 on 2021/3/9.
//
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

#include "DebugTitleScene.h"
#include "StartScene.h"
#include "TitleScene.h"
#include "PhysicsDebugScene.h"
#include "GameScene.h"
#include "NewStoryScene.h"

bool DebugTitleScene::init()
{
    if (!Scene::init())
        return false;

    this->initDebugScenes();

    const auto visibleSize = _director->getVisibleSize();
    const auto layer = Layer::create();

    TTFConfig ttfConfig("fonts/Deng.ttf", 20);
    auto startY = visibleSize.height - 30;

    auto it = this->_sceneNames.cbegin();
    auto index = 0;
    while (it != this->_sceneNames.cend())
    {
        const auto title = *it;
        const auto callback = _sceneCallbacks.at(index);
        const auto label = Label::createWithTTF(ttfConfig, title);
        label->setPosition(visibleSize.width / 2, startY);
        layer->addChild(label);

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);   //设置吞没事件
        listener->onTouchBegan = [callback](Touch* t, Event * e) {
            // 获取事件所绑定的 target
            const auto target = dynamic_cast<Label*>(e->getCurrentTarget());
            // 获取当前点击点所在相对按钮的位置坐标
            const Vec2 locationInNode = target->convertToNodeSpace(t->getLocation());
            const Size s = target->getContentSize();
            const Rect rect = Rect(0, 0, s.width, s.height);

            // 点击范围判断检测
            if (rect.containsPoint(locationInNode))
            {
                auto scene = callback();
                Director::getInstance()->replaceScene(scene);
                return true;

            }
            return false;
        };

        _director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

        startY -= 40;
        it++;
        index++;
    }

    auto scrollView = ScrollView::create(Size(visibleSize.width, visibleSize.height), layer);
    scrollView->setDelegate(this);
    this->addChild(scrollView);

    return true;
}

void DebugTitleScene::scrollViewDidScroll(ScrollView *view)
{
    ScrollViewDelegate::scrollViewDidScroll(view);
}

void DebugTitleScene::scrollViewDidZoom(ScrollView *view)
{
    ScrollViewDelegate::scrollViewDidZoom(view);
}

void DebugTitleScene::initDebugScenes()
{
    _addDebugScene("开始场景", [](){ return StartScene::create(); });
    _addDebugScene("标题场景", [](){ return TitleScene::create(); });
    _addDebugScene("物理测试场景", []() { return PhysicsDebugScene::create(); });
    _addDebugScene("游戏第1关", []() {
        const auto gameScene = GameScene::create();
        gameScene->loadLevel("01");
        return gameScene;
    });
    _addDebugScene("新故事场景测试", []() {
        return NewStoryScene::create("00");
    });
}

void DebugTitleScene::_addDebugScene(const string &name, const std::function<cocos2d::Scene *()> callback)
{
    _sceneNames.push_back(name);
    _sceneCallbacks.push_back(callback);
}
