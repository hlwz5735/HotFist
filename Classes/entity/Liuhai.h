//
//  Liuhai.h
//  HelloCpp
//
//  Created by Ricardo on 14/9/22.
//
//

#ifndef _Liuhai_h__
#define _Liuhai_h__

#include "Enemy.h"

class Liuhai : public Enemy {
public:
    CREATE_FUNC(Liuhai);
    bool init() override;

    void setAttackRect(float dt);

    void refresh(float dt) override;

    void attack() override;

    // 初始化碰撞框
    void initRigidbody() override;

    void initSprite() override;

    // 继承他爷爷的
    void hurt() override;

    // 头部受伤
    void headHurt() override;

    // 腹部受伤
    void flankHurt() override;

    // 浮空受伤
    void airHurt() override;

    // 受伤动画播放完成后的回调
    void hurtCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType type, const char *name);

    // 受伤后处理移动的回调
    void doHurt(float dt);

    void airAttack();

    void groundAttack();

    // 攻击动作的实现函数
    void riderKick();

    void riderSting1();

    void riderSting2();

    void upAttack();

    void saberAttack();
};

#endif