#ifndef _GameLayer__
#define _GameLayer__

#include "cocos2d.h"
#include "Global.h"
#include "../entity/Enemy.h"
#include "../readers/LevelData.h"

class Hero;

class GameLayer : public ax::Layer {
public:
    GameLayer();
    CREATE_FUNC(GameLayer);
    bool init() override;

    virtual void loadData(const std::string &jsonPath);

    void update(float delta) override;

    // ----------- getter / setter -------------
    Hero *getHero() const { return this->hero; }
    const std::vector<ax::Rect> &getStaticBlockVector() { return staticBlockVector; }
    // -----------------------------------------

protected:
    virtual void initMap();
    // 初始化当前地图的所有碰撞矩形
    void initGroundRect();
    //初始化怪物容器
    virtual void initEnemyArr();

    /** 更新物理世界 */
    void updatePhysicsWorld(float delta);
    //调用平常情况下的主角的刷新
    void updateHero();
    //敌人的更新
    void updateEnemy();
    //敌人的行为
    void updateAI();

    void updateCamera();

    LevelData levelData;
    ax::Size stageSize;

    Hero *hero;
    // 敌人容器
    ax::Vector<Enemy *> enemyArr;

    int tileCountX, tileCountY;
    std::vector<ax::Rect> staticBlockVector;
    ax::TMXTiledMap *map;

    // 游戏完成状态
    bool gameFinished = false;

#if defined(DebugDrawRects)
    ax::DrawNode *drawNode;
    void updateDebugDraw();
#endif
};

#endif
