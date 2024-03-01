//
//  Ninja.h
//  HelloCpp
//
//  Created by 田子桐 on 14-8-21.
//
//

#ifndef _Ninja_h
#define _Ninja_h

#include "Enemy.h"

class Ninja : public Enemy {
public:
    void setAttackRect(float dt);

    void refresh(float dt) override;

    void attack() override;

    bool init() override;

    //初始化碰撞框
    void initRigidbody() override;

    void initSprite() override;

    //继承他爷爷的
    void hurt() override;

    //头部受伤
    void headHurt() override;

    //腹部受伤
    void flankHurt() override;

    //浮空受伤
    void airHurt() override;

    //受伤动画播放完成后的回调
    void hurtCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType type, const char *name);

    //受伤后处理移动的回调
    void doHurt(float dt);

    void airAttack();

    void groundAttack();

    //攻击动作的实现函数
    void Dart();

    void Hurt_in_theAir();

    void Boomerang();

    CREATE_FUNC(Ninja);
};


#endif
