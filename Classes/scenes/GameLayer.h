#ifndef _GameLayer__
#define _GameLayer__

#include "cocos2d.h"
#include "Global.h"
#include "../entity/Enemy.h"
#include "../readers/LevelData.h"

USING_NS_CC;

class Hero;

class GameLayer : public Layer {
public:
    GameLayer();
    bool init() override;
    CREATE_FUNC(GameLayer);

    virtual void loadData(std::string jsonPath);

    void update(float delta) override;

    Hero *getHero() const { return this->hero; }
    const std::vector<Rect> &getStaticBlockVector() { return staticBlockVector; }

protected:
    Hero *hero;

    int tileCountX, tileCountY;
    std::vector<Rect> staticBlockVector;
    TMXTiledMap *map;

    // 敌人容器
    Vector<Enemy *> enemyArr;

    // 游戏完成状态
    bool gameFinished = false;

    Size stageSize;

    LevelData levelData;

    virtual void initMap();

    // 初始化当前地图的所有碰撞矩形
    void initGroundRect();

    //初始化怪物容器
    virtual void initEnemyArr();

    /** 更新物理世界 */
    void updatePhysicsWorld(float delta);

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
