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

USING_NS_CC;

class Ninja : public Enemy {
public:
    void setAttackRect(float dt);

    virtual void refresh(float dt);

    virtual void attack();

    virtual bool init();

    //初始化碰撞框
    virtual void initBlock();

    virtual void initSprite();

    //继承他爷爷的
    virtual void hurt();

    //头部受伤
    void headHurt();

    //腹部受伤
    void flankHurt();

    //浮空受伤
    void airHurt();

    //受伤动画播放完成后的回调
    void hurtCallBack(Armature *armature, MovementEventType type, const char *name);

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
