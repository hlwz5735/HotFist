#ifndef _ENTITY_HEADER_FLAG_H__
#define _ENTITY_HEADER_FLAG_H__

#include "cocos2d.h"
#include "cocostudio/CCArmature.h"
#include "Global.h"
#include "AttackRect.h"

USING_NS_CC;
using namespace cocostudio;

/**
 * Entity类，作为所有在地图上显示的物体的对象的父类存在
 * 是Enemy和Hero类的父类
 */
class Entity : public Node {
public:
    Entity();
    // 定义玩家状态
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

public:
    virtual bool init() override;

    //初始化碰撞框
    virtual void initBlock();

    //获取主角碰撞矩形
    Rect getRect();
    AttackRect getAttackRect();

    //初始化精灵动画（代替bindSprite用）
    virtual void initSprite();

    //获取玩家的状态
    EntityState getState();

    void setHP(int a); //修改HP
    void setSP(int a); //修改SP
    //修改玩家的状态
    void setState(EntityState a);

public:
    //新的主角精灵
    Armature *m_sprite;
    //角色的碰撞框
    Rect m_block;
    //角色的攻击框
    AttackRect m_attack;
    //攻击力
    int force;
    //浮空标志
    bool inTheAir_flag;
    //角色的面向，左为true右为false
    bool faceto;
    //有没有成功按下跳跃键的标志
    bool finished;
    //给修正待机姿势用的一个标志
    bool jumpMainFlag;

    //水平方向速度
    float velocityX;
    //竖直方向速度
    float velocityY;

    CREATE_FUNC(Entity);

private:
    //State of the hero
    EntityState state;
public:
    float HP, SP;

    // 更新函数，每秒调用60次
    virtual void update(float dt) override;

    //////////////各种动作////////////////
    //主角修正
    virtual void refresh(float dt);

    //行走（主角的仅仅是播放动画，不同敌人移动速度有区别）
    virtual void run();

    //设置方向（通用）
    void setDirection(bool a);

    //改变方向
    virtual void changeDirection();

    //跳跃（不同的高度不同）
    virtual void jump();

    virtual //跳跃的回调
    void doJump(float dt);

    //受伤
    virtual void hurt();

    //头部受伤
    virtual void headHurt();

    //腹部受伤
    virtual void flankHurt();

    //浮空受伤
    virtual void airHurt();

    //由下蹲站起执行完毕后的回调函数
    virtual void standUpCallBack(Armature *armature, MovementEventType type, const char *name);

    //跳跃动画播放完毕后的回调函数
    virtual void jumpCallBack(Armature *armature, MovementEventType type, const char *name);
};

#endif