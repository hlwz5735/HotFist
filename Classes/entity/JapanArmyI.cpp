/*
 * 重写了攻击动作函数attack
 * 敌人的攻击动作随机产生
 */
#include "cocostudio/Armature.h"
#include "JapanArmyI.h"

USING_NS_AX;
using namespace cocostudio;

bool JapanArmyI::init() {
    if (!Enemy::init()) {
        return false;
    }
    hp = 100;
    view = 5 * 32;
    enemyState = EnemyState::STADINGBY;
    initViewRect();
    speedX = 1.5;
    return true;
}

void JapanArmyI::initRigidbody() {
    this->rigidBody.setBody(Rect(0, 0, 63 - 5, 113));
}

void JapanArmyI::initSprite() {
    ArmatureDataManager::getInstance()->addArmatureFileInfo(
        "Xinfeng0.png",
        "Xinfeng0.plist",
        "Xinfeng.ExportJson");
    armature = Armature::create("Xinfeng");
    // 设置当前运行动画的索引，一个“工程”可以建立多个动画
    armature->getAnimation()->play("Stand");
    // 设置位置信息
    armature->setPosition(25, 0);
    // 添加到容器，当前运行的场景之中
    this->addChild(armature);
}

void JapanArmyI::hurt() {
    if (this->getState() != EntityState::HURT) {
        this->setState(EntityState::HURT);
        // velocityX = 0;
        if (isInTheAir()) {
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

void JapanArmyI::headHurt() {
    armature->getAnimation()->play("HeadHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(JapanArmyI::hurtCallBack));
}

void JapanArmyI::flankHurt() {
    armature->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(JapanArmyI::hurtCallBack));
}

void JapanArmyI::airHurt() {
    // if (faceto) {
    //     velocityX = 2;
    // } else {
    //     velocityX = -2;
    // }
    // velocityY = 5;
    armature->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(JapanArmyI::hurtCallBack));
}

void JapanArmyI::doHurt(float dt) {
    setState(EntityState::NORMAL);
    armature->getAnimation()->play("Stand");
}

void JapanArmyI::hurtCallBack(CCArmature *armature, MovementEventType type, const char *name) {
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

void JapanArmyI::attack() {
    if (getState() == EntityState::NORMAL || getState() == EntityState::WALKING) {
        if (getState() != EntityState::ATTACKING) {
            setState(EntityState::ATTACKING);
            if (this->enemyState != EnemyState::ATTACK) {
                enemyState = EnemyState::ATTACK;
            }
            // velocityX = 0;
            if (isInTheAir()) {
                airAttack();
            } else {
                groundAttack();
            }
        }
    }
}

void JapanArmyI::refresh(float dt) {
    this->setState(EntityState::NORMAL);
    enemyState = EnemyState::STADINGBY;
    armature->getAnimation()->play("Stand");
    attackRect.setFinished(true);
}

void JapanArmyI::setAttackRect(float dt) {
    auto rect = Rect(
        getPositionX() - 40,
        getPositionY() + 16,
        armature->getContentSize().width - 10,
        armature->getContentSize().height - 10
    );
    if (direction) {
        rect.origin.x -= 40;
    } else {
        rect.origin.x += 40;
    }
    this->attackRect = AttackRect(rect, power, false);
}

void JapanArmyI::heavyPunch() {
    armature->getAnimation()->play("HeavyPunch");
    power = 10;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::setAttackRect), 0.4f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::refresh), 0.6f);
}

void JapanArmyI::pistol() {
    armature->getAnimation()->play("Pistol");
    power = 20;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::setAttackRect), 0.4f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::refresh), 0.6f);
}

void JapanArmyI::upAttack() {
    armature->getAnimation()->play("UpAttack");
    power = 10;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::setAttackRect), 0.4f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::refresh), 0.6f);
}

void JapanArmyI::boxingPunch() {
    armature->getAnimation()->play("BoxingPunch");
    power = 15;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::setAttackRect), 0.4f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::refresh), 0.6f);
}

void JapanArmyI::superPistol() {
    armature->getAnimation()->play("SuperPistol");
    power = 30;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::setAttackRect), 0.4f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(JapanArmyI::refresh), 0.6f);
}

void JapanArmyI::airAttack() {
    ;
}

void JapanArmyI::groundAttack() {
    CCLOG("IN JapanArmyI I attacked You");
    int attackIndex = static_cast<int>(AXRANDOM_0_1() * 100);
    if (attackIndex <= 30) {
        heavyPunch();
    } else if (attackIndex <= 55) {
        pistol();
    } else if (attackIndex <= 65) {
        upAttack();
    } else if (attackIndex <= 75) {
        boxingPunch();
    } else if (attackIndex <= 90) {
        heavyPunch();
    } else {
        superPistol();
    }
}
