#ifndef  _STARTSCENE__
#define  _STARTSCENE__

#include "cocos2d.h"
#include "Global.h"

USING_NS_CC;

class StartScene : public Scene {
public:
    StartScene() {

    }

    ~StartScene() {

    }

    //动态文字函数
    void labelAction(Sprite *pLabel, Point pLabelPoint);

    void labelActionMoveTo(Sprite *pLabelMove, Point pLabelPointMove);

    virtual bool init();

    virtual bool onTouchBegan(Touch* touch, Event *pEvent);

    void toTitleScene();

    static Scene *createScene();

    Sprite *text;

    void labelonStage(float dt);

    CREATE_FUNC(StartScene);
};

#endif
