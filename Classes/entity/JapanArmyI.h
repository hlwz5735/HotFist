#ifndef _JapanArmyI__
#define _JapanArmyI__

#include "Enemy.h"

USING_NS_CC;

class JapanArmyI : public Enemy {
public:
    CREATE_FUNC(JapanArmyI);
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
    void hurtCallBack(Armature *armature, MovementEventType type, const char *name);

    // 受伤后处理移动的回调
    void doHurt(float dt);

    void airAttack();

    void groundAttack();

    //攻击动作的实现函数
    void heavyPunch();

    void pistol();

    void upAttack();

    void boxingPunch();

    void superPistol();
};

#endif