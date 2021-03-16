#ifndef _GameOverLayer__
#define _GameOverLayer__

#include "cocos2d.h"
USING_NS_CC;

/************************************************************************
 * GameOverLayer:游戏结束界面
 * 包含一个背景图片和一个“回到标题”的按钮，切换到该页面的时候会播放音乐
 ************************************************************************/
class GameOverLayer : public Layer
{
public:
	virtual bool init();
	static Scene* Scene();
	CREATE_FUNC(GameOverLayer);

	//Button Callback Functions:
	void retryBtnCallBack(Ref* pSender);
private:
	MenuItemImage* retryBtn;
	Sprite* sp_Background;
};

#endif