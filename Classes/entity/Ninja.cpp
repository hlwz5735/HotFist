//
//  Ninja.cpp
//  HelloCpp
//
//  Created by 田子桐 on 14-8-21.
//
//

#include "cocostudio/Armature.h"
#include "Ninja.h"

USING_NS_AX;
using namespace cocostudio;

bool Ninja::init() {
    if (!Enemy::init()) {
        return false;
    }
    hp = 500;
    view = 5 * 32;
    enemyState = EnemyState::STADINGBY;
    //初始化精灵动画
    initSprite();
    initViewRect();
    speedX = 1.5;
    return true;
}

void Ninja::initRigidbody() {
    Entity::initRigidbody();
}

void Ninja::initSprite() {
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Ninja0.png", "Ninja0.plist", "Ninja.ExportJson");
    // 这里直接使用Nivida ，而此信息保存在 Nivida.ExportJson 中，与其创建的项目属性相对应
    armature = Armature::create("Ninja");
    // 设置当前运行动画的索引，一个“工程”可以建立多个动画
    armature->getAnimation()->play("Stand");
    // 设置位置信息
    armature->setPosition(Point(25, 0));
    // 添加到容器，当前运行的场景之中
    this->addChild(armature);
}

void Ninja::hurt() {
    Enemy::hurt();
}

void Ninja::headHurt() {
    armature->getAnimation()->play("HeadHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Ninja::hurtCallBack));
}

void Ninja::flankHurt() {
    armature->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Ninja::hurtCallBack));
}

void Ninja::airHurt() {
    // if (faceto) {
    //     velocityX = 2;
    // } else {
    //     velocityX = -2;
    // }
    // velocityY = 5;
    armature->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Ninja::hurtCallBack));
}

void Ninja::doHurt(float dt) {
    setState(EntityState::NORMAL);
    armature->getAnimation()->play("Stand");
}

void Ninja::hurtCallBack(Armature *armature, MovementEventType type, const char *name) {
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

void Ninja::attack() {
    Enemy::attack();
}

void Ninja::refresh(float dt) {
    this->setState(EntityState::NORMAL);
    enemyState = EnemyState::STADINGBY;
    armature->getAnimation()->play("Stand");
}

void Ninja::setAttackRect(float dt) {
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

void Ninja::Dart() {
    armature->getAnimation()->play("Dart");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::setAttackRect), 0.6f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::refresh), 0.4f);
}

void Ninja::Hurt_in_theAir() {
    armature->getAnimation()->play("Hurt_in_theAir");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::setAttackRect), 0.6f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::refresh), 0.4f);
}

void Ninja::Boomerang() {
    armature->getAnimation()->play("Boomerang");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::setAttackRect), 0.6f);
    scheduleOnce(AX_SCHEDULE_SELECTOR(Ninja::refresh), 0.4f);
}

void Ninja::airAttack() {
    ;
}

void Ninja::groundAttack() {
    int attackIndex = static_cast<int>(AXRANDOM_0_1() * 100);
    if (attackIndex <= 30) {
        Dart();
    } else if (attackIndex <= 65) {
        Hurt_in_theAir();
    } else {
        Boomerang();
    }
}
