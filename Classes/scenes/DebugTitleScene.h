﻿//
// Created by 厉猛 on 2021/3/9.
//

#ifndef HOTFISTREMASTER_DEBUGTITLESCENE_H
#define HOTFISTREMASTER_DEBUGTITLESCENE_H

#include "cocos2d.h"
#include "GUI/ScrollView/ScrollView.h"
USING_NS_AX;
using namespace cocos2d::extension;

class DebugTitleScene: public Scene, public ScrollViewDelegate
{
public:
    bool init() override;

    CREATE_FUNC(DebugTitleScene);

    void scrollViewDidScroll(ScrollView *view) override;

    void scrollViewDidZoom(ScrollView *view) override;

private:
    void _addFrameSizeDebugLayer();
    void initDebugScenes();
    void _addDebugScene(const std::string &name, const std::function<cocos2d::Scene* ()> callback);
    std::vector<std::string> _sceneNames;
    std::vector<std::function<cocos2d::Scene* ()>> _sceneCallbacks;
    // std::unordered_map<std::string, std::function<cocos2d::Scene* ()>> _sceneMap;
};


#endif //HOTFISTREMASTER_DEBUGTITLESCENE_H
