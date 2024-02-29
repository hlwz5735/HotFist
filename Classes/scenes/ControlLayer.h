#ifndef _ControlLayer__
#define _ControlLayer__

#include "cocos2d.h"
#include "../entity/Hero.h"

USING_NS_CC;

class ControlLayer : public Layer {
public:
    ControlLayer();

    CREATE_FUNC(ControlLayer);

    bool init() override;

    void update(float delta) override;

    void jmpBtnCallBack(Ref *pSender);

    void atkBtnCallBack(Ref *pSender);

    void bladeBtnCallBack(Ref *pSender);

    void shieldBtnCallBack(Ref *pSender);

    void cloakBtnCallBack(Ref *pSender);

    void clockUPBtnCallBack(Ref *pSender);

    void pauseBtnCallBack(Ref *pSender);

    void stopPlayer();

    void setHero(Hero *h) { hero = h; }

private:
    // 取得对主角的操纵权
    Hero *hero;

    bool isLeftBtnPressed;
    bool isRightBtnPressed;

    //主角状态框显示用
    Sprite *imageItemSide;
    Sprite *imageItem;
    Sprite *hp_Bar;
    Sprite *sp_Bar;
    Sprite *tp_Bar;

private:
#if DESKTOP_RUNTIME
    // 电脑端的话，加上键盘监听
    void addKeyEventListener();
#endif
    void _bindEventListener(Node *node);
};
#endif
