#ifndef _ControlLayer__
#define _ControlLayer__

#include "cocos2d.h"
#include "Global.h"
#include "../entity/Hero.h"

class ControlLayer : public ax::Layer {
public:
    ControlLayer();

    CREATE_FUNC(ControlLayer);

    bool init() override;

    void update(float delta) override;

    void bladeBtnCallBack(Ref *pSender);
    void shieldBtnCallBack(Ref *pSender);
    void cloakBtnCallBack(Ref *pSender);
    void clockUPBtnCallBack(Ref *pSender);
    void pauseBtnCallBack(Ref *pSender);

    void setHero(Hero *h) { hero = h; }

private:
#if DESKTOP_RUNTIME
    // 电脑端的话，加上键盘监听
    void addKeyEventListener();
#endif

    void bindEventListener(Node *node);

    Hero *hero;

    // 主角状态框显示用
    ax::Sprite *imageItemSide;
    ax::Sprite *imageItem;
    ax::Sprite *hp_Bar;
    ax::Sprite *sp_Bar;
    ax::Sprite *tp_Bar;
};

#endif
