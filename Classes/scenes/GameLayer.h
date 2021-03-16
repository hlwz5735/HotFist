#ifndef _GameLayer__
#define _GameLayer__

#include "cocos2d.h"
#include "Global.h"
#include "LevelData.h"
#include "Enemy.h"

USING_NS_CC;

class Hero;

class GameLayer : public Layer {
public:
    GameLayer();

    virtual bool init() override;
    virtual void loadData(std::string jsonPath);
    virtual void update(float delta);


    Hero* getHero() { return this->hero; }

    CREATE_FUNC(GameLayer);

protected:
    TMXTiledMap *map = nullptr;
    int tileCountX, tileCountY;
    Hero *hero;

    std::vector<Rect> staticBlockVector;

    // 敌人容器
    Vector<Enemy*> enemyArr;
    // 游戏完成状态
    bool gameFinished = false;

    Size stageSize;

    LevelData levelData;

protected:
    virtual void initMap();
    //初始化当前地图的所有碰撞矩形
    void initGroundRect();

    //初始化怪物容器
    virtual void initEnemyArr();

    //调用平常情况下的主角的刷新
    void updateHero();

    //地图的刷新
    void updateMap();

    //敌人的更新
    void updateEnemy();

    //敌人的行为
    void updateAI();

    Point updateCameraPosition();

#if defined(DebugDrawRects)
    DrawNode *drawNode;
    void updateDebugDraw();
#endif
};

#endif