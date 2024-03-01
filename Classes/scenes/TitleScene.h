#ifndef _TitleScene_H__
#define _TitleScene_H__

#include "cocos2d.h"
/************************************************************************
 * TitleLayer:标题界面的类，用于显示标题界面
 * 游戏启动后进入的第一个画面，需要包含“新游戏”、“继续游戏”、“制作组”、“退出游戏四个选项
 * 游戏的左上角需要有一个”齐鲁软件设计大赛“的标志
 ************************************************************************/
USING_NS_AX;

class TitleScene : public Scene {
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

    CREATE_FUNC(TitleScene);

    //Button Callback Functions:
    void newGmeBtnCallBack(Ref *pSender);

    void ctnGmeBtnCallBack(Ref *pSender);

    void tmStudBtnCallBack(Ref *pSender);

    void quitGmeBtnCallBack(Ref *pSender);

private:
    MenuItemImage *newGmeBtn;
    MenuItemImage *ctnGmeBtn;
    MenuItemImage *tmStudBtn;
    MenuItemImage *quitGmeBtn;
};

#endif
