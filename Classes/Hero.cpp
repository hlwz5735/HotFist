#include "audio/AudioEngine.h"
#include "cocostudio/Armature.h"
#include "Hero.h"

USING_NS_CC;
using namespace cocostudio;

Hero::Hero()
: m_mode(HeroMode::SHIELD)
, TP(0)
{
    this->HP = 100;
    this->SP = 100;
}

bool Hero::init() {
    if (!Entity::init()) {
        return false;
    }
    // 初始化状态
    setState(EntityState::NORMAL);
    setHP(100);
    setSP(100);
    // 初始化三大数据
    TP = 0;
    // 初始化模式状态
    m_mode = HeroMode::SHIELD;
    // 初始化水平和竖直方向的速度
    velocityY = 0;
    faceto = false;
    inTheAir_flag = true;
    // 初始化动画
    initSprite();
    // 初始化碰撞框
    initBlock();

    AudioEngine::preload("Audio/Cloak.mp3");
    AudioEngine::preload("Audio/Clock.mp3");
    AudioEngine::preload("Audio/e.mp3");
    AudioEngine::preload("Audio/ea.mp3");
    AudioEngine::preload("Audio/en.mp3");
    AudioEngine::preload("Audio/haaaaa.mp3");
    AudioEngine::preload("Audio/heng.mp3");
    AudioEngine::preload("Audio/kale.mp3");
    AudioEngine::preload("Audio/maxArmor.mp3");
    AudioEngine::preload("Audio/seiya.mp3");
    AudioEngine::preload("Audio/souyuken.mp3");


    return true;
}

void Hero::initSprite() {
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Nivida0.png", "Nivida0.plist", "Nivida.ExportJson");
    // 这里直接使用Nivida ，而此信息保存在 Nivida.ExportJson 中，与其创建的项目属性相对应
    m_sprite = Armature::create("Nivida");
    // 设置当前运行动画的索引，一个“工程”可以建立多个动画
    m_sprite->getAnimation()->play("Stand");
    // 设置位置信息
    m_sprite->setPosition(Point(25, 0));
    // 添加到容器，当前运行的场景之中
    this->addChild(m_sprite);
}

void Hero::initBlock() {
    m_block = Rect(getPositionX(),getPositionY(),
            m_sprite->getContentSize().width - 5,m_sprite->getContentSize().height);
}

void Hero::run() {
    // 在空中的时候什么也不做
    if (inTheAir_flag) {}
    // 不在空中，判断是不是其它状态
    else
    {
        if (getState() == EntityState::NORMAL) {
            if (getMode() == HeroMode::LIGHTBLADE) {
                m_sprite->getAnimation()->play("SB_Walk");
            } else
                m_sprite->getAnimation()->play("Walk");
            setState(EntityState::WALKING);
        }
    }
    if (getState() == EntityState::NORMAL || getState() == EntityState::WALKING) {
        if (getMode() != HeroMode::CLOCKUP) {
            if (m_mode == HeroMode::INVISIBLE) {
                SP -= 0.6f;
            }
            if (!faceto)
                this->velocityX = 2;
            else
                this->velocityX = -2;
        } else {
            SP -= 0.7f;
            if (!faceto)
                this->velocityX = 10;
            else
                this->velocityX = -10;
        }
    }
}

Hero::HeroMode Hero::getMode() {
    return m_mode;
}

void Hero::setMode(HeroMode a) {
    m_mode = a;
}

void Hero::hurt() {
    if (this->getState() != EntityState::HURT) {
        this->setState(EntityState::HURT);
        // 护盾模式下，所有受伤动作均引导向防御动作
        if (m_mode == HeroMode::SHIELD)
        {
            if (inTheAir_flag) {
                AudioEngine::play2d("Audio/ea.mp3");
                // 因为没有空中防御，所以用这个代替
                airHurt();
            } else {
                const float tempRand = AXRANDOM_0_1();
                // 在头部防御和腹部防御之间随机出一个
                if (tempRand < 0.5f)
                {
                    AudioEngine::play2d("Audio/e.mp3");
                    headDefence();
                } else {
                    AudioEngine::play2d("Audio/en.mp3");
                    flankDefence();
                }
            }
        }
        // 光剑模式有几个独有的受伤动作
        else if (m_mode == HeroMode::LIGHTBLADE)
        {
            if (inTheAir_flag) {
                AudioEngine::play2d("Audio/e.mp3");
                // 因为没有空中防御，所以用这个代替
                SB_FlankHurt();
            } else {
                const float tempRand = AXRANDOM_0_1();
                // 在头部防御和腹部防御之间随机出一个
                if (tempRand < 0.5f)
                {
                    AudioEngine::play2d("Audio/ea.mp3");
                    SB_HeadHurt();
                } else {
                    AudioEngine::play2d("Audio/en.mp3");
                    SB_FlankHurt();
                }
            }
        }
        // 其他模式
        else
        {
            if (inTheAir_flag) {
                AudioEngine::play2d("Audio/e.mp3");
                airHurt();
            } else {
                const float tempRand = AXRANDOM_0_1();
                // 在头部防御和腹部防御之间随机出一个
                if (tempRand < 0.5f)
                {
                    AudioEngine::play2d("Audio/en.mp3");
                    headHurt();
                } else {
                    AudioEngine::play2d("Audio/ea.mp3");
                    flankHurt();
                }
            }
        }
    }
}

void Hero::headDefence() {
    m_sprite->getAnimation()->play("HeadDefence");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::flankDefence() {
    m_sprite->getAnimation()->play("FlankDefence");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::headHurt() {
    m_sprite->getAnimation()->play("HeadHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::flankHurt() {
    m_sprite->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::SB_FlankHurt() {
    m_sprite->getAnimation()->play("SB_FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::SB_HeadHurt() {
    m_sprite->getAnimation()->play("SB_HeadHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::airHurt() {
    if (faceto) {
        velocityX = 2;
    } else {
        velocityX = -2;
    }
    velocityY = 5;
    m_sprite->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    m_sprite->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::doHurt(float dt) {
    ActionInterval *temp;
    if (faceto) {
        temp = MoveBy::create(0.1f, Point(10, 0));
    } else {
        temp = MoveBy::create(0.1f, Point(-10, 0));
    }
    this->runAction(temp);
    setState(EntityState::NORMAL);
}

void Hero::hurtCallBack(Armature *armature, MovementEventType type, const char *name) {
    CCLOG("movement callback name:%s \n", name);
    if (strcmp(name, "FlankDefence") == 0 || strcmp(name, "HeadDefence") == 0 || strcmp(name, "HeadHurt") == 0 || strcmp(name, "FlankHurt") == 0) {
        switch (type) {
            case COMPLETE:
                setState(EntityState::NORMAL);
                armature->getAnimation()->play("Stand");
                break;
            default:
                break;
        }
    }
    if (strcmp(name, "SB_FlankHurt") == 0 || strcmp(name, "SB_FlankHurt") == 0) {
        switch (type) {
            case COMPLETE:
                setState(EntityState::NORMAL);
                armature->getAnimation()->play("SB_Stand");
                break;
            default:
                break;
        }
    }
}

void Hero::attack() {
    if (getMode() != HeroMode::LIGHTBLADE) {
        normalAttack();
    } else {
        bladeAttack();
    }
}

void Hero::bladeAttack() {

    if (getState() == EntityState::NORMAL || getState() == EntityState::WALKING) {
        setState(EntityState::ATTACKING);
        if (inTheAir_flag) {
            airAttack();
        } else {
            groundBladeAttack();
        }
    }
}

void Hero::normalAttack() {
    if (getState() == EntityState::NORMAL || getState() == EntityState::WALKING) {
        setState(EntityState::ATTACKING);
        if (inTheAir_flag) {
            airAttack();
        } else {
            groundAttack();
        }
    }
}

void Hero::airAttack() {
    AudioEngine::play2d("Audio/seiya.mp3");
    if (getMode() == HeroMode::LIGHTBLADE) {
        m_sprite->getAnimation()->play("RiderSting");
        force = 25;
        if (faceto)
            velocityX = -5;
        else
            velocityX = 5;
        this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
        this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.5f);
    } else {
        m_sprite->getAnimation()->play("RiderKick");
        if (faceto)
            velocityX = -5;
        else
            velocityX = 5;
        force = 20;
        this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
        this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.5f);
    }

    setState(EntityState::NORMAL);
}

void Hero::groundAttack() {
    const int temp = static_cast<int>(AXRANDOM_0_1() * 4 + 1);
    switch (temp) {
        case 1:
            heavyPunch();
            break;
        case 2:
            upAttack();
            break;
        case 3:
            heavyKick();
            break;
        default:
            terminateAttack();
            break;
    }
}

void Hero::terminateAttack() {
    const int temp = static_cast<int>(AXRANDOM_0_1() * 100);
    if (temp < 50) {
        drangonPunch();
    } else {
        cycloneKick();
    }
}

void Hero::groundBladeAttack() {
    const int temp = static_cast<int>(AXRANDOM_0_1() * 4 + 1);
    switch (temp) {
        case 1:
            SB_Attack1();
            break;
        case 2:
            SB_Attack2();
            break;
        case 3:
            SB_Attack3();
            break;
        default:
            SB_Attack4();
            break;
    }
}

void Hero::heavyPunch() {
    AudioEngine::play2d("Audio/hea.mp3");
    m_sprite->getAnimation()->play("HeavyPunch");
    force = 20;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::upAttack() {
    AudioEngine::play2d("Audio/heng.mp3");
    m_sprite->getAnimation()->play("UpAttack");
    force = 20;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::heavyKick() {
    AudioEngine::play2d("Audio/heng.mp3");
    m_sprite->getAnimation()->play("HeavyKick");
    force = 20;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::SB_Attack1() {
    AudioEngine::play2d("Audio/heng.mp3");
    m_sprite->getAnimation()->play("Saber1");
    force = 28;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::SB_Attack2() {
    AudioEngine::play2d("Audio/heng.mp3");
    m_sprite->getAnimation()->play("Saber2");
    force = 28;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::SB_Attack3() {
    AudioEngine::play2d("Audio/heng.mp3");
    m_sprite->getAnimation()->play("Saber3");
    force = 30;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::SB_Attack4() {
    AudioEngine::play2d("Audio/heng.mp3");
    m_sprite->getAnimation()->play("Saber4");
    force = 35;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::drangonPunch() {
    AudioEngine::play2d("Audio/souyuken.mp3");
    int temp = static_cast<int>(getPositionY());
    setPositionY(temp + 10);
    setState(EntityState::NORMAL);
    inTheAir_flag = true;
    initBlock();
    velocityY = 10;
    if (faceto)
        velocityX = -2;
    else
        velocityX = 2;
    m_sprite->getAnimation()->play("DrangonPunch");
    force = 120;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.6f);
}

void Hero::cycloneKick() {
    m_sprite->getAnimation()->play("CycloneKick");
    AudioEngine::play2d("Audio/kale.mp3");
    force = 135;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.3f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.6f);
}

void Hero::refresh(float dt) {
    this->setState(EntityState::NORMAL);
    m_attack.isFinished = true;
    velocityX = 0;
    if (getMode() == HeroMode::LIGHTBLADE) {
        m_sprite->getAnimation()->play("SB_Stand");
    } else
        m_sprite->getAnimation()->play("Stand");
}

void Hero::setAttackRect(float dt) {
    auto rect = Rect(
            getPositionX() - 40,
            getPositionY() + 16,
            m_sprite->getContentSize().width - 10,
            m_sprite->getContentSize().height - 10
    );
    if (faceto)
    {
        rect.origin.x -= 40;
    }
    else
    {
        rect.origin.x += 40;
    }
    this->m_attack = AttackRect(rect, force, false);
}

void Hero::handBlade() {
    if (inTheAir_flag) {
        if (getMode() == HeroMode::LIGHTBLADE) {
            setMode(HeroMode::SHIELD);
        } else
            setMode(HeroMode::LIGHTBLADE);
    } else {
        if (getMode() == HeroMode::LIGHTBLADE) {
            m_sprite->getAnimation()->play("Stand");
            setMode(HeroMode::SHIELD);
        } else {
            setState(EntityState::FORCED);
            m_sprite->getAnimation()->playByIndex(13);
            AudioEngine::play2d("Audio/haaaaa.mp3");
            scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterHandBlade), 1.0f);
        }
    }
}

void Hero::afterHandBlade(float dt) {
    setMode(HeroMode::LIGHTBLADE);
    setState(EntityState::NORMAL);
    m_sprite->getAnimation()->playByIndex(18);
    m_sprite->setOpacity(255);
    m_sprite->setColor(Color3B(255, 255, 255));
}

void Hero::jump() {
    if (!inTheAir_flag && !finished) {
        finished = true;
        if (getMode() == HeroMode::LIGHTBLADE) {
            m_sprite->getAnimation()->play("SB_Jump");
        } else
            m_sprite->getAnimation()->play("Jump");
        this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doJump), 0.33f);
    }
}

void Hero::doJump(float dt) {
    int temp = static_cast<int>(getPositionY());
    if (getMode() == HeroMode::LIGHTBLADE) {
        m_sprite->getAnimation()->play("SB_Up");
    } else
        m_sprite->getAnimation()->play("Up");
    setState(EntityState::NORMAL);
    setPositionY(temp + 10);
    initBlock();
    inTheAir_flag = true;
    finished = false;
    // 在此处确定修正待机动画
    jumpMainFlag = false;
    velocityY = 14;
}

void Hero::modeShield() {
    setMode(HeroMode::SHIELD);
    setState(EntityState::NORMAL);
    m_sprite->setOpacity(255);
    m_sprite->setColor(Color3B(255, 255, 255));
    AudioEngine::play2d("Audio/maxArmor.mp3");
    m_sprite->getAnimation()->play("Stand");
}

void Hero::modeIvisible() {
    if (inTheAir_flag) {
        setMode(HeroMode::INVISIBLE);
        scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterModeIvisible), 0.6f);
    } else {
        if (getMode() != HeroMode::INVISIBLE) {
            setState(EntityState::FORCED);
            m_sprite->getAnimation()->play("ModeChange");
            AudioEngine::play2d("Audio/Cloak.mp3");
            scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterModeIvisible), 0.6f);
        }
    }
}

void Hero::afterModeIvisible(float dt) {
    setMode(HeroMode::INVISIBLE);
    setState(EntityState::NORMAL);
    m_sprite->setOpacity(50);
    m_sprite->setColor(Color3B(0, 0, 200));
    m_sprite->getAnimation()->play("Stand");
}

void Hero::modeClockUp() {
    if (inTheAir_flag) {
        setMode(HeroMode::CLOCKUP);
        scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterModeClockUp), 0.6f);
    } else {
        if (getMode() != HeroMode::CLOCKUP) {
            setState(EntityState::FORCED);
            m_sprite->getAnimation()->play("ModeChange");
            AudioEngine::play2d("Audio/Clock.mp3");
            scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterModeClockUp), 0.6f);
        }
    }
}

void Hero::afterModeClockUp(float dt) {
    setMode(HeroMode::CLOCKUP);
    setState(EntityState::NORMAL);
    m_sprite->setColor(Color3B(30, 255, 40));
    m_sprite->setOpacity(255);
    m_sprite->getAnimation()->play("Stand");
}

void Hero::update(float dt) {
    Entity::update(dt);
    //主角的状态设置
    if (this->SP > 0) {
        if (this->getMode() == HeroMode::INVISIBLE) {
            this->SP -= 0.2f;
        } else if (this->getMode() == HeroMode::CLOCKUP) {
            this->SP -= 0.1f;
        } else if (this->getMode() == HeroMode::LIGHTBLADE) {
            this->SP -= 0.1f;
        } else {
            this->SP += 0.1f;
        }
    } else {
        this->modeShield();
        this->SP += 1;
    }
    if (this->TP < 100) {
        this->TP += 0.07f;
    } else {
        this->HP = 100;
        this->SP = 100;
        this->TP = 0;
    }
    if (this->HP < 0) {
        this->HP = 0;
    }
    if (this->HP > 100) {
        this->HP = 100;
    }
    if (this->SP < 0) {
        this->SP = 0;
    }
    if (this->SP > 100) {
        this->SP = 100;
    }
    if (this->TP < 0) {
        this->TP = 0;
    }
    if (this->TP > 100) {
        this->TP = 100;
    }
}
