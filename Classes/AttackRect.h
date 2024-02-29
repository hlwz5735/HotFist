#ifndef _AttackRect__
#define _AttackRect__

#include "cocos2d.h"

USING_NS_CC;

class AttackRect : public Rect {
public:
    AttackRect();

    AttackRect(float x, float y, float width, float height, int force, bool t_isCanFly);

    AttackRect(const Rect &a, int force, bool t_isCanFly);

    AttackRect(const AttackRect &other);

    AttackRect &operator=(const AttackRect &o);

    bool isFinished() const { return finished; }
    void setFinished(bool f) { finished = f; }
    bool isBlowUp() const { return isCanFly; }
    int getPower() const { return m_force; }
    void setPower(const int p) { m_force = p; }

private:
    // 攻击的威力
    int m_force;
    // 是否造成击飞
    bool isCanFly;
    // 是否已经攻击标志
    bool finished;
};

#endif
