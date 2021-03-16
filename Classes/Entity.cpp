#include "Entity.h"

USING_NS_CC;
using namespace cocostudio;


Entity::Entity()
: m_attack(AttackRect())
, state(EntityState::NORMAL)
, HP(0)
, SP(0)
, velocityX(0)
, velocityY(0)
, force(0)
, finished(false)
, faceto(false)
, inTheAir_flag(true)
, jumpMainFlag(true)
{}

bool Entity::init() {
    return Node::init();
}

void Entity::initSprite()
{

}

Rect Entity::getRect() {
    return m_block;
}

AttackRect Entity::getAttackRect() {
    return m_attack;
}

Entity::EntityState Entity::getState() {
    return state;
}

void Entity::setState(EntityState a) {
    state = a;
}

void Entity::initBlock() {
    m_block = Rect(getPositionX() + 20, getPositionY(), 28, 91);
}

void Entity::setHP(int a) {
    HP = a;
}

void Entity::setSP(int a) {
    SP = a;
}

void Entity::run() {
    setState(EntityState::WALKING);
    if (!faceto)
        this->velocityX = 1.5f;
    else
        this->velocityX = -1.5f;
}

void Entity::setDirection(bool a) {
    faceto = a;
    if (a)        //面向左
        m_sprite->setScaleX(-1.0f);
    else
        m_sprite->setScaleX(1.0f);
}

void Entity::changeDirection() {
    if (faceto) {
        faceto = false;
        m_sprite->setScaleX(1.0f);
    } else {
        faceto = true;
        m_sprite->setScaleX(-1.0f);
    }
}

void Entity::jump() {
    if (!inTheAir_flag && !finished) {
        finished = true;
        m_sprite->getAnimation()->play("Jump");
        this->scheduleOnce(schedule_selector(Entity::doJump), 0.33f);
    }
}

void Entity::doJump(float dt) {
    int temp = (int) getPositionY();
    m_sprite->getAnimation()->play("Up");
    setPositionY(temp + 10);
    initBlock();
    inTheAir_flag = true;
    finished = false;
    jumpMainFlag = false;        //在此处确定修正待机动画
    velocityY = 14;
    setState(EntityState::NORMAL);
}

//
void Entity::standUpCallBack(Armature *armature, MovementEventType type, const char *name) {
    CCLOG("movement callback name:%s \n", name);
    if (strcmp(name, "Down") == 0) {
        switch (type) {
            case COMPLETE:
                //setState(NORMAL);
                armature->getAnimation()->play("Stand");
                break;
            default:
                break;
        }
    }
}

//
void Entity::jumpCallBack(Armature *armature, MovementEventType type, const char *name) {
    CCLOG("movement callback name:%s \n", name);
    if (strcmp(name, "Jump") == 0) {
        switch (type) {
            case COMPLETE:
                setState(EntityState::NORMAL);
                armature->getAnimation()->play("Up");
                break;
            default:
                break;
        }
    }
}

void Entity::hurt() {
    setState(EntityState::HURT);
    if (inTheAir_flag)                                //浮空的话就出浮空受伤
    {
        airHurt();
    } else {
        float tempRand = CCRANDOM_0_1();
        if (tempRand < 0.5f)                        //在头部受伤和腹部受伤之间随机出一个
        {
            headHurt();
        } else {
            flankHurt();
        }
    }
}

//下面三个函数在不同的子类里有不同的实现，这里的三个只是卖萌
void Entity::headHurt() {
    CCLOG("Oh,my head!\n");
    setState(EntityState::NORMAL);
}

void Entity::flankHurt() {
    CCLOG("Oh,my baby!\n");
    setState(EntityState::NORMAL);
}

void Entity::airHurt() {
    CCLOG("I want to fly so high\n");
    setState(EntityState::NORMAL);
}

void Entity::refresh(float dt) {
    this->setState(EntityState::NORMAL);
    m_attack.isFinished = true;
    m_sprite->getAnimation()->play("Stand");
}

void Entity::update(float dt) {
    Node::update(dt);
}
