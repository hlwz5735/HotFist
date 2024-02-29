#ifndef HOTFISTREMASTER_PHYSICSDEBUGSCENE_H
#define HOTFISTREMASTER_PHYSICSDEBUGSCENE_H

#include "cocos2d.h"
#include "../readers/LevelData.h"
USING_NS_CC;

class PhysicsDebugScene : public Scene
{
public:
    bool init() override;

    CREATE_FUNC(PhysicsDebugScene);

private:
    LevelData levelData;
};


#endif //HOTFISTREMASTER_PHYSICSDEBUGSCENE_H
