#ifndef _Story__
#define _Story__

#include "cocos2d.h"
#include "audio/AudioEngine.h"
#include "../Global.h"

USING_NS_AX;

class Story : public Layer {
public:
    Story();

    virtual bool init() override;

    Sprite *dialogBox_bottom;
    Sprite *dialogBox_top;
    Sprite *crctorImage_bottom;
    Sprite *crctorImage_top;

    Sprite *text_bottom;
    Sprite *text_top;

    //标记当前是否可以触屏跳转到下一事件
    bool state;
    //事件ID标记
    int count;
public:

    void showAmysImage();

    void showNividasImage();

    void showNormansImage();

    //跳转到下一个事件的函数
    virtual void nextEvt() = 0;

    //清除所有内容
    void clear();

    //触摸监听函数三人行
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
};

#endif
