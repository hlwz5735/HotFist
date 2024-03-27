#include "Enemy.h"
#include "cocostudio/Armature.h"

USING_NS_AX;
using namespace cocostudio;

bool Enemy::init() {    //大部分数据都是在基类或者派生类里面初始化的，所以这个初始化函数就比较水……
    if (!Entity::init()) {
        return false;
    }
    view = 0;
    enemyState = EnemyState::STADINGBY;
    count = 0;
    speedX = 1.5f;
    return true;
}

void Enemy::initViewRect() {
	//face to the Left,x may be - view
	if (!direction)
        m_ViewRect = Rect(
                getPositionX() - view - 20,
                getPositionY() - 80,
                view + 20,
                armature->getContentSize().height * 2);
    else
        m_ViewRect = Rect(
                getPositionX() - 20,
                getPositionY() - 80,
                view + 20,
                armature->getContentSize().height * 2);
}

void Enemy::attack() {
    CCLOG("I attacked you");
}

void Enemy::useSkill() {
    CCLOG("Byu!");
}

void Enemy::patrol() {
    if (this->enemyState == EnemyState::PATROLING) {
        count++;
        // this->run();
        if (count == 100 || getPositionX() <= 10) {
            this->flipDirection();
        }
    }
}
