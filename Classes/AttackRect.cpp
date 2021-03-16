#include "AttackRect.h"

USING_NS_CC;

AttackRect::AttackRect() {
    setRect(0, 0, 0, 0);
    m_force = 0;
    isCanFly = false;
    isFinished = false;
}

AttackRect::AttackRect(float x, float y, float width, float height, int force = 0, bool t_isCanFly = false)
        : Rect(x, y, width, height) {
    m_force = force;
    isCanFly = t_isCanFly;
    isFinished = false;
}

AttackRect::AttackRect(Rect &a, int force = 0, bool t_isCanFly = false) : Rect(a) {
    m_force = force;
    isCanFly = t_isCanFly;
    isFinished = false;
}

AttackRect::AttackRect(const AttackRect &other) {
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
    m_force = other.m_force;
    isFinished = other.isFinished;
    isCanFly = other.isCanFly;
}
