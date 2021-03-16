#ifndef _AttackRect__
#define _AttackRect__

#include "cocos2d.h"

USING_NS_CC;

class AttackRect : public Rect {
public:
	// 是否已经攻击标志
	bool isFinished;
	// 是否造成击飞
	bool isCanFly;
	// 攻击的威力
	int m_force;

    AttackRect();

    AttackRect(float x, float y, float width, float height, int force, bool t_isCanFly);

    AttackRect(Rect &a, int force, bool t_isCanFly);

    AttackRect(const AttackRect &other);
};

#endif
