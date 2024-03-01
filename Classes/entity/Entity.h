#ifndef _ENTITY_HEADER_FLAG_H__
#define _ENTITY_HEADER_FLAG_H__

#include "cocos2d.h"
#include "cocostudio/Armature.h"
#include "AttackRect.h"
#include "RigidBody.h"

/**
 * Entity类，作为所有在地图上显示的物体的对象的父类存在
 * 是Enemy和Hero类的父类
 */
class Entity : public ax::Node {
public:
    // 玩家状态
    enum class EntityState {
        // 正常状态
        NORMAL = 0,
        // 行走状态
        WALKING,
        // 攻击状态
        ATTACKING,
        // 受伤状态
        HURT,
        // 强制状态
        FORCED
    };

    enum Direction {
        LEFT = -1,
        RIGHT = 1
    };

    Entity();

    CREATE_FUNC(Entity);

    bool init() override;
    // 初始化精灵动画
    virtual void initSprite();
    // 初始化碰撞框
    virtual void initRigidbody();

    // 更新函数，每秒调用60次
    void update(float dt) override;

    //////////////各种动作////////////////
    // 主角修正
    virtual void refresh(float dt);

    // 跳跃（不同的高度不同）
    virtual void jump();

    // 跳跃的回调
    virtual void doJump(float dt);

    // 受伤
    virtual void hurt();

    // 头部受伤
    virtual void headHurt();

    // 腹部受伤
    virtual void flankHurt();

    // 浮空受伤
    virtual void airHurt();

    // 跳跃动画播放完毕后的回调函数
    virtual void jumpCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType type, const char *name);
    // 由下蹲站起执行完毕后的回调函数
    virtual void standUpCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType type, const char *name);

    const AttackRect &getAttackRect() const { return attackRect; }
    EntityState getState() const { return state; }
    void setState(EntityState a) { state = a; }
    float getHp() const { return hp; }
    void setHp(const float a) { hp = a; }
    float getSp() const { return sp; }
    void setSP(const float a) { sp = a; }
    const cocostudio::Armature *getArmature() const { return armature; }
    cocostudio::ArmatureAnimation *getAnimation() const {
        if (!armature) {
            return nullptr;
        }
        return armature->getAnimation();
    }
    bool getDirection() const { return direction; }
    void setDirection(Direction f);
    void flipDirection() { setDirection(static_cast<Direction>(-direction)); }
    bool isInTheAir() const { return !rigidBody.isGrounded(); }
    RigidBody &getRigidBody() { return rigidBody; }

protected:
    cocostudio::Armature *armature;

    EntityState state;
    RigidBody rigidBody;
    float hp, sp;
    Direction direction;
    // 角色的攻击框
    AttackRect attackRect;

    // ----------- 实体数据 -------------
    /// 攻击力
    int power;
    float moveSpeed;
    // ---------------------------------
};

#endif