#include "AttackRect.h"

USING_NS_AX;

AttackRect::AttackRect(): m_force(0), isCanFly(false), finished(false) {
}

AttackRect::AttackRect(float x, float y, float width, float height, int force = 0, bool t_isCanFly = false)
    : Rect(x, y, width, height), m_force(force), isCanFly(t_isCanFly), finished(false) {
}

AttackRect::AttackRect(const Rect &a, int force = 0, bool t_isCanFly = false)
    : Rect(a), m_force(force), isCanFly(t_isCanFly), finished(false) {
}

AttackRect::AttackRect(const AttackRect &other)
    : Rect(other), m_force(other.m_force), isCanFly(other.isCanFly), finished(other.finished) {
}

AttackRect &AttackRect::operator=(const AttackRect &o) {
    setRect(o.origin.x, o.origin.y, o.size.width, o.size.height);
    m_force = o.m_force;
    isCanFly = o.isCanFly;
    finished = o.finished;
    return *this;
}
