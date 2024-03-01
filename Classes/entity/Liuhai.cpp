//
//  Liuhai.cpp
//  HelloCpp
//
//  Created by Ricardo on 14/9/22.
//

#include "cocostudio/Armature.h"
#include "Liuhai.h"

USING_NS_AX;
using namespace cocostudio;

bool Liuhai::init() {
    if (!Enemy::init()) {
        return false;
    }
    setHp(1000);
    view = 5 * 32;
    enemyState = EnemyState::STADINGBY;
    //初始化精灵动画
    initSprite();
    initViewRect();
    speedX = 1.5;
    return true;
}

void Liuhai::initRigidbody() {
    Entity::initRigidbody();
}

void Liuhai::initSprite() {
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Liuhai0.png", "Liuhai0.plist", "Liuhai.ExportJson");
    armature = Armature::create("Liuhai");
    // 设置当前运行动画的索引，一个“工程”可以建立多个动画
    armature->getAnimation()->play("Stand");
    // 设置位置信息
    armature->setPosition(25, 0);
    // 添加到容器，当前运行的场景之中
    this->addChild(armature);
}

void Liuhai::hurt() {
    Enemy::hurt();
}

void Liuhai::headHurt() {
    armature->getAnimation()->play("HeadHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Liuhai::hurtCallBack));
}

void Liuhai::flankHurt() {
    armature->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Liuhai::hurtCallBack));
}

void Liuhai::airHurt() {
    // if (faceto) {
    //     velocityX = 2;
    // } else {
    //     velocityX = -2;
    // }
    // velocityY = 5;
    armature->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Liuhai::hurtCallBack));
}

void Liuhai::doHurt(float dt) {
    setState(EntityState::NORMAL);
    armature->getAnimation()->play("Stand");
}

void Liuhai::hurtCallBack(Armature *armature, MovementEventType type, const char *name) {
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

void Liuhai::attack() {
    Enemy::attack();
}

void Liuhai::refresh(float dt) {
    this->setState(EntityState::NORMAL);
    enemyState = EnemyState::STADINGBY;
    attackRect.setFinished(true);
    // velocityX = 0;
    armature->getAnimation()->play("Stand");
}

void Liuhai::setAttackRect(float dt) {
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

void Liuhai::riderKick() {
    armature->getAnimation()->play("RiderKick");
    power = 30;
    // if (faceto) {
    //     velocityX = -2;
    // } else
    //     velocityX = 2;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::setAttackRect), 0.4f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::refresh), 0.6f);
}

void Liuhai::riderSting2() {
    armature->getAnimation()->play("RiderSting2");
    power = 30;
    // if (faceto) {
    //     velocityX = -3;
    // } else {
    //     velocityX = 3;
    // }
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::setAttackRect), 0.4f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::refresh), 0.6f);
}

void Liuhai::upAttack() {
    armature->getAnimation()->play("WAttack");
    power = 45;
    // if (faceto) {
    //     velocityX = -3;
    // } else {
    //     velocityX = 3;
    // }
    // velocityY = 1;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::setAttackRect), 0.4f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::refresh), 0.6f);
}

void Liuhai::saberAttack() {
    armature->getAnimation()->play("Saber");
    power = 50;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::setAttackRect), 0.5f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::refresh), 0.6f);
}

void Liuhai::riderSting1() {
    armature->getAnimation()->play("RiderSting1");
    power = 30;
    // if (faceto) {
    //     velocityX = -2;
    // } else {
    //     velocityX = 2;
    // }
    // velocityY = 1.5;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::setAttackRect), 0.4f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(Liuhai::refresh), 0.6f);
}

void Liuhai::airAttack() {
}

void Liuhai::groundAttack() {
    CCLOG("IN Liuhai I attacked You");
    int attackIndex = static_cast<int>(AXRANDOM_0_1() * 100);
    if (attackIndex <= 30) {
        riderKick();
    } else if (attackIndex <= 55) {
        riderSting2();
    } else if (attackIndex <= 65) {
        upAttack();
    } else if (attackIndex <= 75) {
        saberAttack();
    } else if (attackIndex <= 90) {
        riderKick();
    } else {
        riderSting1();
    }
}
