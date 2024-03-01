#ifndef _PauseLayer__
#define _PauseLayer__

#include "cocos2d.h"
USING_NS_AX;

class PauseLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PauseLayer);

	void btnResume(Ref* pSender);
};
#endif