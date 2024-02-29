//
//  JapanArmyII.cpp
//  HelloCpp
//
//  Created by 田子桐 on 14-8-19.
//
//
#include "cocostudio/Armature.h"
#include "JapanArmyII.h"


USING_NS_CC;
using namespace cocostudio;

bool JapanArmyII::init() {
    if (!Enemy::init()) {
        return false;
    }
    hp = 120;
    view = 5 * 32;
    enemyState = EnemyState::STADINGBY;
    initSprite(); //初始化精灵动画
    initViewRect();
    speedX = 1.5;
    return true;
}

void JapanArmyII::initBlock() {
    m_block = Rect(
        getPositionX(),
        getPositionY(),
        m_sprite->getContentSize().width - 5,
        m_sprite->getContentSize().height);
}

void JapanArmyII::initSprite() {
    ArmatureDataManager::getInstance()->addArmatureFileInfo(
        "Xinfeng0.png",
        "Xinfeng0.plist",
        "Xinfeng.ExportJson");
    m_sprite = Armature::create("Xinfeng");
    // 设置当前运行动画的索引，一个“工程”可以建立多个动画
    m_sprite->getAnimation()->play("Stand");
    // 设置位置信息
    m_sprite->setPosition(Point(25, 0));
    m_sprite->setColor(Color3B(200, 0, 0));
    // 添加到容器，当前运行的场景之中
    this->addChild(m_sprite);
}

void JapanArmyII::hurt() {
    if (this->getState() != EntityState::HURT) {
        this->setState(EntityState::HURT);
        velocityX = 0;
        if (inTheAirFlag) {
            airHurt();
        } else {
            float tempRand = AXRANDOM_0_1();
            //在头部防御和腹部防御之间随机出一个
            if (tempRand < 0.5f) {
                headHurt();
            } else {
                flankHurt();
            }
        }
    }
}

void JapanArmyII::headHurt() {
    m_sprite->getAnimation()->play("HeadHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(JapanArmyII::hurtCallBack));
}

void JapanArmyII::flankHurt() {
    m_sprite->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(JapanArmyII::hurtCallBack));
}

void JapanArmyII::airHurt() {
    if (faceto) {
        velocityX = 2;
    } else {
        velocityX = -2;
    }
    velocityY = 5;
    m_sprite->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(JapanArmyII::hurtCallBack));
}

void JapanArmyII::doHurt(float dt) {
    setState(EntityState::NORMAL);
    m_sprite->getAnimation()->play("Stand");
}

void JapanArmyII::hurtCallBack(Armature *armature, MovementEventType type, const char *name) {
    if (strcmp(name, "FlankDefence") == 0 || strcmp(name, "HeadDefence") == 0) {
        switch (type) {
            case COMPLETE:
                setState(EntityState::NORMAL);
                armature->getAnimation()->play("Stand");
                break;
            default:
                break;
        }
    }
}

void JapanArmyII::attack() {
    if (getState() == EntityState::NORMAL || getState() == EntityState::WALKING) {
        if (getState() != EntityState::ATTACKING) {
            setState(EntityState::ATTACKING);
            if (this->enemyState != EnemyState::ATTACK) {
                enemyState = EnemyState::ATTACK;
            }
            velocityX = 0;
            if (inTheAirFlag) {
                airAttack();
            } else {
                groundAttack();
            }
        }
    }
}

void JapanArmyII::refresh(float dt) {
    this->setState(EntityState::NORMAL);
    enemyState = EnemyState::STADINGBY;
    m_attack.setFinished(true);
    m_sprite->getAnimation()->play("Stand");
}

void JapanArmyII::setAttackRect(float dt) {
    auto rect = Rect(
        getPositionX() - 40,
        getPositionY() + 16,
        m_sprite->getContentSize().width - 10,
        m_sprite->getContentSize().height - 10
    );
    if (faceto) {
        rect.origin.x -= 40;
    } else {
        rect.origin.x += 40;
    }
    this->m_attack = AttackRect(rect, force, false);
}

void JapanArmyII::HeavyPunch() {
    m_sprite->getAnimation()->play("HeavyPunch");
    force = 10;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::setAttackRect), 0.3f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::refresh), 0.4f);
}

void JapanArmyII::Pistol() {
    m_sprite->getAnimation()->play("Pistol");
    force = 20;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::setAttackRect), 0.3f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::refresh), 0.4f);
}

void JapanArmyII::UpAttack() {
    m_sprite->getAnimation()->play("UpAttack");
    force = 10;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::setAttackRect), 0.3f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::refresh), 0.4f);
}

void JapanArmyII::BoxingPunch() {
    m_sprite->getAnimation()->play("BoxingPunch");
    force = 15;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::setAttackRect), 0.3f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::refresh), 0.4f);
}

void JapanArmyII::SuperPistol() {
    m_sprite->getAnimation()->play("SuperPistol");
    force = 30;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::setAttackRect), 0.3f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyII::refresh), 0.4f);
}

void JapanArmyII::airAttack() {
    ;
}

void JapanArmyII::groundAttack() {
    int attackIndex = static_cast<int>(AXRANDOM_0_1() * 100);
    if (attackIndex <= 30) {
        HeavyPunch();
    } else if (attackIndex <= 55) {
        Pistol();
    } else if (attackIndex <= 65) {
        UpAttack();
    } else if (attackIndex <= 75) {
        BoxingPunch();
    } else if (attackIndex <= 90) {
        HeavyPunch();
    } else {
        SuperPistol();
    }
}
