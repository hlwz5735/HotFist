//
//  Liuhai.cpp
//  HelloCpp
//
//  Created by Ricardo on 14/9/22.
//

#include "cocostudio/CCArmature.h"
#include "Liuhai.h"

USING_NS_CC;

bool Liuhai::init()
{
    if (!Enemy::init())
    {
        return false;
    }
    setHP(1000);
    view = 5 * 32;
    enemyState = EnemyState::STADINGBY;
    //初始化精灵动画
    initSprite();
    initViewRect();
    speedX = 1.5;
    return true;
}

void Liuhai::initBlock()
{
    m_block = Rect(getPositionX(), getPositionY(),
            m_sprite->getContentSize().width - 5, m_sprite->getContentSize().height);
}

void Liuhai::initSprite()
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Liuhai0.png", "Liuhai0.plist", "Liuhai.ExportJson");
    m_sprite = Armature::create("Liuhai");
    // 设置当前运行动画的索引，一个“工程”可以建立多个动画
    m_sprite->getAnimation()->play("Stand");
    // 设置位置信息
    m_sprite->setPosition(25, 0);
    // 添加到容器，当前运行的场景之中
    this->addChild(m_sprite);
}

void Liuhai::hurt()
{
    if (this->getState() != EntityState::HURT)
    {
        this->setState(EntityState::HURT);
        velocityX = 0;
        if (inTheAir_flag)
        {
            airHurt();
        }
        else
        {
            float tempRand = CCRANDOM_0_1();
            //在头部防御和腹部防御之间随机出一个
            if (tempRand < 0.5f)
            {
                headHurt();
            }
            else
            {
                flankHurt();
            }
        }
    }
}

void Liuhai::headHurt()
{
    m_sprite->getAnimation()->play("HeadHurt");
    this->scheduleOnce(schedule_selector(Liuhai::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Liuhai::hurtCallBack));
}

void Liuhai::flankHurt()
{
    m_sprite->getAnimation()->play("FlankHurt");
    this->scheduleOnce(schedule_selector(Liuhai::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Liuhai::hurtCallBack));
}

void Liuhai::airHurt()
{
    if (faceto)
    {
        velocityX = 2;
    }
    else
    {
        velocityX = -2;
    }
    velocityY = 5;
    m_sprite->getAnimation()->play("FlankHurt");
    this->scheduleOnce(schedule_selector(Liuhai::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Liuhai::hurtCallBack));
}

void Liuhai::doHurt(float dt)
{
    setState(EntityState::NORMAL);
    m_sprite->getAnimation()->play("Stand");
}

void Liuhai::hurtCallBack(CCArmature *armature, MovementEventType type, const char *name)
{
    if (strcmp(name, "FlankDefence") == 0 || strcmp(name, "HeadDefence") == 0)
    {
        switch (type)
        {
            case COMPLETE:
                setState(EntityState::NORMAL);
                armature->getAnimation()->play("Stand");
                break;
            default:
                break;
        }
    }
}

void Liuhai::attack()
{
    if (getState() == EntityState::NORMAL || getState() == EntityState::WALKING)
    {
        if (getState() != EntityState::ATTACKING)
        {
            setState(EntityState::ATTACKING);
            if (this->enemyState != EnemyState::ATTACK)
            {
                enemyState = EnemyState::ATTACK;
            }
            velocityX = 0;
            if (inTheAir_flag)
            {
                airAttack();
            }
            else
            {
                groundAttack();
            }
        }
    }
}

void Liuhai::refresh(float dt)
{
    this->setState(EntityState::NORMAL);
    enemyState = EnemyState::STADINGBY;
    m_attack.isFinished = true;
    velocityX = 0;
    m_sprite->getAnimation()->play("Stand");
}

void Liuhai::setAttackRect(float dt)
{
    auto rect = Rect(
            getPositionX() - 40,
            getPositionY() + 16,
            m_sprite->getContentSize().width - 10,
            m_sprite->getContentSize().height - 10
    );
    if (faceto)
    {
        rect.origin.x -= 40;
    }
    else
    {
        rect.origin.x += 40;
    }
    this->m_attack = AttackRect(rect, force, false);
}

void Liuhai::HeavyPunch()
{
    m_sprite->getAnimation()->play("RiderKick");
    force = 30;
    if (faceto)
    {
        velocityX = -2;
    }
    else
        velocityX = 2;
    this->scheduleOnce(schedule_selector(Liuhai::setAttackRect), 0.4f);
    this->scheduleOnce(schedule_selector(Liuhai::refresh), 0.6f);
}

void Liuhai::Pistol()
{
    m_sprite->getAnimation()->play("RiderSting2");
    force = 30;
    if (faceto)
    {
        velocityX = -3;
    }
    else
        velocityX = 3;
    this->scheduleOnce(schedule_selector(Liuhai::setAttackRect), 0.4f);
    scheduleOnce(schedule_selector(Liuhai::refresh), 0.6f);
}

void Liuhai::UpAttack()
{
    m_sprite->getAnimation()->play("WAttack");
    force = 45;
    if (faceto)
    {
        velocityX = -3;
    }
    else
        velocityX = 3;
    velocityY = 1;
    this->scheduleOnce(schedule_selector(Liuhai::setAttackRect), 0.4f);
    scheduleOnce(schedule_selector(Liuhai::refresh), 0.6f);
}

void Liuhai::BoxingPunch()
{
    m_sprite->getAnimation()->play("Saber");
    force = 50;
    this->scheduleOnce(schedule_selector(Liuhai::setAttackRect), 0.5f);
    scheduleOnce(schedule_selector(Liuhai::refresh), 0.6f);
}

void Liuhai::SuperPistol()
{
    m_sprite->getAnimation()->play("RiderSting1");
    force = 30;
    if (faceto)
    {
        velocityX = -2;
    }
    else
        velocityX = 2;
    velocityY = 1.5;
    this->scheduleOnce(schedule_selector(Liuhai::setAttackRect), 0.4f);
    scheduleOnce(schedule_selector(Liuhai::refresh), 0.6f);
}

void Liuhai::airAttack()
{
    ;
}

void Liuhai::groundAttack()
{
    CCLOG("IN Liuhai I attacked You");
    int attackIndex = static_cast<int>(CCRANDOM_0_1() * 100);
    if (attackIndex <= 30)
    {
        HeavyPunch();
    }
    else if (attackIndex <= 55)
    {
        Pistol();

    }
    else if (attackIndex <= 65)
    {
        UpAttack();
    }
    else if (attackIndex <= 75)
    {
        BoxingPunch();
    }
    else if (attackIndex <= 90)
    {
        HeavyPunch();
    }
    else
    {
        SuperPistol();
    }
    //enemyState = STADINGBY;
}