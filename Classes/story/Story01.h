#ifndef _Story01__
#define _Story01__

#include "cocos2d.h"
#include "../Global.h"
#include "Story.h"

USING_NS_AX;

class Story01 : public Story
{
public:
    Story01()
    {
    }

    ~Story01()
    {
    }

    virtual bool init() override;

    virtual void onEnter() override;

    virtual void nextEvt() override;

    Sprite *backgroundImage;

    void event01();

    void event02();

    void event03();

    void event04();

    CREATE_FUNC(Story01);

    static Scene *createScene();
};

#endif
