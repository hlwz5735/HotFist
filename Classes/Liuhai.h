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

USING_NS_CC;

class Liuhai : public Enemy {
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

    //	virtual void initViewRect();
    void airAttack();

    void groundAttack();

    //攻击动作的实现函数
    void HeavyPunch();

    void Pistol();

    void UpAttack();

    void BoxingPunch();

    void SuperPistol();

    CREATE_FUNC(Liuhai);
};

#endif