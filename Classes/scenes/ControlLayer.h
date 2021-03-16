#ifndef _ControlLayer__
#define _ControlLayer__
#include "cocos2d.h"
#include "SceneFactory.h"
#include "Hero.h"
USING_NS_CC;
class ControlLayer: public Layer
{
public:
    ControlLayer();
    virtual bool init();
    CREATE_FUNC(ControlLayer);

    virtual void update(float delta);

    void JmpBtnCallBack(Ref* pSender);
    void AtkBtnCallBack(Ref* pSender);
    void BladeBtnCallBack(Ref* pSender);
    void ShieldBtnCallBack(Ref* pSender);
    void CloakBtnCallBack(Ref* pSender);
    void ClockUPBtnCallBack(Ref* pSender);
    void pauseBtnCallBack(Ref* pSender);

    void stopPlayer();
public:
    // 取得对主角的操纵权
    Hero* hero;

    bool isLeftBtnPressed;
    bool isRightBtnPressed;

    //主角状态框显示用
    Sprite* imageItemSide;
    Sprite* imageItem;
    Sprite* hp_Bar;
    Sprite* sp_Bar;
    Sprite* tp_Bar;

private:
#if DESKTOP_RUNTIME
    // 电脑端的话，加上键盘监听
    void addKeyEventListener();
#endif
    void _bindEventListener(Node *node);
};
#endif
