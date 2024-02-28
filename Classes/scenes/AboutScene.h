#ifndef __GROUPLAYER_H_
#define __GROUPLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class AboutScene : public Scene
{
public:
    bool init();

    Ref *menuReturnCall(Ref *pSender);

    CREATE_FUNC(AboutScene);
};

#endif