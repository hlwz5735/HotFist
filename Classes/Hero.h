#ifndef _Hero__
#define _Hero__

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

class Hero : public Entity
{
public:
    Hero();
    enum class HeroMode
    {
        // 护盾模式
        SHIELD = 0,
        // 高速模式
        CLOCKUP,
        // 潜行模式
        INVISIBLE,
        // 力场控制模式
        FORCECONTROL,
        // 光剑状态
        LIGHTBLADE,
        // 手枪状态
        PISTOL,
        // 手榴弹状态
        SHOTPUT,
        // RPG火箭炮状态
        RPG
    };
public:
    // 怒气值
    float TP;

    virtual bool init();

    // 初始化碰撞框
    virtual void initBlock();

    virtual void initSprite();

    virtual void run();

    // 获取玩家模式状态
    HeroMode getMode();

    // 修改玩家模式状态
    void setMode(HeroMode a);

    // 重写父类的这三个受伤函数
    virtual void hurt();

    virtual void headHurt();

    virtual void flankHurt();

    virtual void airHurt();

    // 头部防御
    void headDefence();

    // 腹部防御
    void flankDefence();

    void SB_HeadHurt();

    void SB_FlankHurt();

    // 受伤动画播放完成后的回调
    void hurtCallBack(Armature *armature, MovementEventType type, const char *name);

    // 受伤后处理移动的回调
    void doHurt(float dt);

    // 总攻击动作
    void attack();

    // 不拿剑的攻击动作
    void normalAttack();

    // 拿剑的攻击动作
    void bladeAttack();

    // 空中攻击动作的分支
    void airAttack();

    // 地面攻击的分支
    void groundAttack();

    // 地面光剑攻击的分支
    void groundBladeAttack();

    void terminateAttack();

    // 被调用分配的动作
    void heavyPunch();

    void upAttack();

    void heavyKick();

    void SB_Attack1();

    void SB_Attack2();

    void SB_Attack3();

    void SB_Attack4();

    // 两个终结技
    void drangonPunch();

    void cycloneKick();

    // 主角修正
    virtual void refresh(float dt) override;

    void setAttackRect(float dt);

    void handBlade();

    void afterHandBlade(float dt);

    void modeShield();

    void modeIvisible();

    void afterModeIvisible(float dt);

    void modeClockUp();

    void afterModeClockUp(float dt);

    virtual void jump() override;

    virtual void doJump(float dt) override;

    void update(float dt) override;

public:
    CREATE_FUNC(Hero);
private:
    // 模式状态
    HeroMode m_mode;
};

#endif
