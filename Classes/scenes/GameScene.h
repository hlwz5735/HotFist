#ifndef HOTFISTREMASTER_GAMESCENE_H
#define HOTFISTREMASTER_GAMESCENE_H

#include "cocos2d.h"

USING_NS_CC;

class GameLayer;
class ControlLayer;

class GameScene : public Scene
{
public:
    virtual bool init() override;

    void loadLevel(const std::string& levelName);

    CREATE_FUNC(GameScene);
private:
    GameLayer* gameLayer;
    ControlLayer* controlLayer;
};


#endif //HOTFISTREMASTER_GAMESCENE_H
