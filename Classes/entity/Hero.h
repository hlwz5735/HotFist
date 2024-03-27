#ifndef _Hero__
#define _Hero__

#include "cocos2d.h"
#include "Entity.h"

class Hero : public Entity
{
public:
    enum HeroMode {
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

    Hero();
    CREATE_FUNC(Hero);

    bool init() override;
    void initSprite() override;

    void update(float dt) override;

    // 重写父类的这三个受伤函数
    void hurt() override;
    void headHurt() override;
    void flankHurt() override;
    void airHurt() override;

    // 头部防御
    void headDefence();
    // 腹部防御
    void flankDefence();
    void SB_HeadHurt();
    void SB_FlankHurt();

    // 受伤动画播放完成后的回调
    void hurtCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType type, const char *name);

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
    void refresh(float dt) override;


    void handBlade();
    void afterHandBlade(float dt);

    void modeShield();
    void modeIvisible();
    void afterModeIvisible(float dt);
    void modeClockUp();
    void afterModeClockUp(float dt);

    float getTp() const { return tp; }
    HeroMode getMode() const { return m_mode; }
    void setMode(HeroMode a) { m_mode = a; }
    void setAttackRect(float dt);
private:
    void updateInput(float delta);
    void updateStatus();

    // 怒气值
    float tp;
    // 模式状态
    HeroMode m_mode;
};

#endif
