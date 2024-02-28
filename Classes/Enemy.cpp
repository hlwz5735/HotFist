#include "Enemy.h"
#include "cocostudio/Armature.h"

USING_NS_CC;
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
	if (!faceto)
        m_ViewRect = Rect(
                getPositionX() - view - 20,
                getPositionY() - 80,
                view + 20,
                m_sprite->getContentSize().height * 2);
    else
        m_ViewRect = Rect(
                getPositionX() - 20,
                getPositionY() - 80,
                view + 20,
                m_sprite->getContentSize().height * 2);
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
        this->run();
        if (count == 100 || getPositionX() <= 10) {
            this->changeDirection();
        }
    }
}

//因为不能声明为纯虚函数，所以只能这样。该函数没有实际作用
void Enemy::initBlock() {}

void Enemy::changeDirection()
{
	//完成父类动作后清零步数，免得敌人蛇精病式巡逻
    Entity::changeDirection();
	count = 0;
}

void Enemy::run() {
	//在空中的时候什么也不做
    if (inTheAir_flag) {}
	//不在空中，判断是不是其它状态
    else
    {
        if (getState() == Entity::EntityState::NORMAL) {
            m_sprite->getAnimation()->play("Walk");
            setState(Entity::EntityState::WALKING);
        }
    }
    if (getState() == Entity::EntityState::WALKING || getState() == Entity::EntityState::NORMAL) {
        if (!faceto)
            velocityX = speedX;
        else
            velocityX = -speedX;
    } else {
        velocityX = 0;
    }
}

void Enemy::jump() {
    if (getState() == Entity::EntityState::NORMAL || getState() == Entity::EntityState::WALKING) {
        if (!inTheAir_flag && !finished) {
            finished = true;
            m_sprite->getAnimation()->play("Jump");
            this->scheduleOnce(AX_SCHEDULE_SELECTOR(Entity::doJump), 0.33f);
        }
    }
}