#ifndef HOTFISTREMASTER_PHYSICSDEBUGSCENE_H
#define HOTFISTREMASTER_PHYSICSDEBUGSCENE_H

#include "cocos2d.h"
#include "thirdparty/box2d/include/box2d/box2d.h"
#include "../readers/LevelData.h"
#include "extensions/axmol-ext.h"
USING_NS_AX;

class PhysicsDebugScene : public Scene
{
public:
    bool init() override;
    CREATE_FUNC(PhysicsDebugScene);

    void update(float delta) override;

private:
    void initBox2dWorld();

    LevelData levelData;
    b2World *world;
    ax::extension::PhysicsDebugNodeBox2D debugDraw;
    ax::DrawNode* drawBox2D;
};


#endif //HOTFISTREMASTER_PHYSICSDEBUGSCENE_H
