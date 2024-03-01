#ifndef _Enemy__
#define _Enemy__

#include "Entity.h"

USING_NS_AX;

class Enemy : public Entity {
public:
    enum class EnemyState {
        // 巡逻中
        PATROLING = 0,
        // 接近主角中
        REACHING,
        // 攻击中，跟HeroState是一回事（敌人在HeroState的ATTACKING属性弃用）
        ATTACK,
        // 强制状态，跟HeroState是一回事（敌人在HeroState的FORCED属性弃用）
        FORCE,
        // 待机中，用于其他状态的结束和巡逻状态的开启
        STADINGBY,
        // 濒死状态，用于显示死亡动画 怪物的HP为0时引导进来，并在播放完动画后标记为DIE
        DYING,
        // 从怪物数组中将此对象删除的标志
        DIE
    };

    bool init() override;
    CREATE_FUNC(Enemy);

    //初始化并更新视野矩形
    virtual void initViewRect();

    void initRigidbody() override;

    // 攻击
    virtual void attack();

    // 施用法术（不同敌人施用法术的场合均不同）
    virtual void useSkill();

    void changeDirection() override;

    // 巡逻
    void patrol();

    void run() override;

    void jump() override;

protected:
    // 怪物状态机枚举
    EnemyState enemyState;
    // 巡逻步数
    int count;
    // 敌人的水平移动速度
    float speedX;
    int view;
    // 视野矩形
    Rect m_ViewRect;
};

#endif
