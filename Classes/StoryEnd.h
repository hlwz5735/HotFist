#ifndef _StoryEnd__
#define _StoryEnd__

#include "cocos2d.h"
#include "Global.h"
#include "SceneFactory.h"
#include "Story.h"

USING_NS_CC;

class StoryEnd : public Story {
public:
    virtual bool init();
    virtual void onEnter() override;

    virtual void nextEvt();

    void animateFinished(Node *sender);

    void backtoTitle(Node *sender);

    CREATE_FUNC(StoryEnd);
};

#endif