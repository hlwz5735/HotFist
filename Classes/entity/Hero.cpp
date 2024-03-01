#include "audio/AudioEngine.h"
#include "cocostudio/Armature.h"
#include "Hero.h"

#include "InputManager.h"

USING_NS_AX;
using namespace cocostudio;

Hero::Hero(): tp(0), m_mode(HeroMode::SHIELD) {
}

bool Hero::init() {
    if (!Entity::init()) {
        return false;
    }
    // 初始化状态
    setState(EntityState::NORMAL);
    // 初始化三大数据
    hp = 100;
    sp = 100;
    tp = 0;
    // 初始化模式状态
    m_mode = HeroMode::SHIELD;

    moveSpeed = 2;
    direction = RIGHT;

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
    ArmatureDataManager::getInstance()->
        addArmatureFileInfo("Nivida0.png", "Nivida0.plist", "Nivida.ExportJson");
    // 这里直接使用Nivida ，而此信息保存在 Nivida.ExportJson 中，与其创建的项目属性相对应
    armature = Armature::create("Nivida");
    // 设置当前运行动画的索引，一个“工程”可以建立多个动画
    armature->getAnimation()->play("Stand");
    // 设置位置信息
    armature->setPosition(Point(25, 0));
    // 添加到容器，当前运行的场景之中
    this->addChild(armature);
}

void Hero::initRigidbody() {
    this->rigidBody.setBody(Rect(0, 0, 63 - 5, 113));
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
        if (m_mode == HeroMode::SHIELD) {
            if (isInTheAir()) {
                AudioEngine::play2d("Audio/ea.mp3");
                // 因为没有空中防御，所以用这个代替
                airHurt();
            } else {
                const float tempRand = AXRANDOM_0_1();
                // 在头部防御和腹部防御之间随机出一个
                if (tempRand < 0.5f) {
                    AudioEngine::play2d("Audio/e.mp3");
                    headDefence();
                } else {
                    AudioEngine::play2d("Audio/en.mp3");
                    flankDefence();
                }
            }
        }
        // 光剑模式有几个独有的受伤动作
        else if (m_mode == HeroMode::LIGHTBLADE) {
            if (isInTheAir()) {
                AudioEngine::play2d("Audio/e.mp3");
                // 因为没有空中防御，所以用这个代替
                SB_FlankHurt();
            } else {
                const float tempRand = AXRANDOM_0_1();
                // 在头部防御和腹部防御之间随机出一个
                if (tempRand < 0.5f) {
                    AudioEngine::play2d("Audio/ea.mp3");
                    SB_HeadHurt();
                } else {
                    AudioEngine::play2d("Audio/en.mp3");
                    SB_FlankHurt();
                }
            }
        }
        // 其他模式
        else {
            if (isInTheAir()) {
                AudioEngine::play2d("Audio/e.mp3");
                airHurt();
            } else {
                const float tempRand = AXRANDOM_0_1();
                // 在头部防御和腹部防御之间随机出一个
                if (tempRand < 0.5f) {
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
    armature->getAnimation()->play("HeadDefence");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::flankDefence() {
    armature->getAnimation()->play("FlankDefence");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::headHurt() {
    armature->getAnimation()->play("HeadHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::flankHurt() {
    armature->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::SB_FlankHurt() {
    armature->getAnimation()->play("SB_FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::SB_HeadHurt() {
    armature->getAnimation()->play("SB_HeadHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::airHurt() {
    // if (faceto) {
    //     velocityX = 2;
    // } else {
    //     velocityX = -2;
    // }
    // velocityY = 5;
    armature->getAnimation()->play("FlankHurt");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doHurt), 0.33f);
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Hero::hurtCallBack));
}

void Hero::doHurt(float dt) {
    ActionInterval *temp;
    if (direction) {
        temp = MoveBy::create(0.1f, Point(10, 0));
    } else {
        temp = MoveBy::create(0.1f, Point(-10, 0));
    }
    this->runAction(temp);
    setState(EntityState::NORMAL);
}

void Hero::hurtCallBack(Armature *armature, MovementEventType type, const char *name) {
    CCLOG("movement callback name:%s \n", name);
    if (strcmp(name, "FlankDefence") == 0 || strcmp(name, "HeadDefence") == 0 || strcmp(name, "HeadHurt") == 0 ||
        strcmp(name, "FlankHurt") == 0) {
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
        if (isInTheAir()) {
            airAttack();
        } else {
            groundBladeAttack();
        }
    }
}

void Hero::normalAttack() {
    if (getState() == EntityState::NORMAL || getState() == EntityState::WALKING) {
        setState(EntityState::ATTACKING);
        if (isInTheAir()) {
            airAttack();
        } else {
            groundAttack();
        }
    }
}

void Hero::airAttack() {
    AudioEngine::play2d("Audio/seiya.mp3");
    if (getMode() == HeroMode::LIGHTBLADE) {
        armature->getAnimation()->play("RiderSting");
        power = 25;
        // if (faceto)
        //     velocityX = -5;
        // else
        //     velocityX = 5;
        this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
        this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.5f);
    } else {
        armature->getAnimation()->play("RiderKick");
        // if (faceto)
        //     velocityX = -5;
        // else
        //     velocityX = 5;
        power = 20;
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
    armature->getAnimation()->play("HeavyPunch");
    power = 20;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::upAttack() {
    AudioEngine::play2d("Audio/heng.mp3");
    armature->getAnimation()->play("UpAttack");
    power = 20;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::heavyKick() {
    AudioEngine::play2d("Audio/heng.mp3");
    armature->getAnimation()->play("HeavyKick");
    power = 20;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::SB_Attack1() {
    AudioEngine::play2d("Audio/heng.mp3");
    armature->getAnimation()->play("Saber1");
    power = 28;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::SB_Attack2() {
    AudioEngine::play2d("Audio/heng.mp3");
    armature->getAnimation()->play("Saber2");
    power = 28;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::SB_Attack3() {
    AudioEngine::play2d("Audio/heng.mp3");
    armature->getAnimation()->play("Saber3");
    power = 30;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::SB_Attack4() {
    AudioEngine::play2d("Audio/heng.mp3");
    armature->getAnimation()->play("Saber4");
    power = 35;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.4f);
}

void Hero::drangonPunch() {
    AudioEngine::play2d("Audio/souyuken.mp3");
    int temp = static_cast<int>(getPositionY());
    setPositionY(temp + 10);
    setState(EntityState::NORMAL);
    initRigidbody();
    // velocityY = 10;
    // if (faceto)
    //     velocityX = -2;
    // else
    //     velocityX = 2;
    armature->getAnimation()->play("DrangonPunch");
    power = 120;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.1f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.6f);
}

void Hero::cycloneKick() {
    armature->getAnimation()->play("CycloneKick");
    AudioEngine::play2d("Audio/kale.mp3");
    power = 135;
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::setAttackRect), 0.3f);
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::refresh), 0.6f);
}

void Hero::refresh(float dt) {
    this->setState(EntityState::NORMAL);
    attackRect.setFinished(true);
    // velocityX = 0;
    if (getMode() == HeroMode::LIGHTBLADE) {
        armature->getAnimation()->play("SB_Stand");
    } else
        armature->getAnimation()->play("Stand");
}

void Hero::setAttackRect(float dt) {
    auto rect = Rect(
        getPositionX() - 40,
        getPositionY() + 16,
        armature->getContentSize().width - 10,
        armature->getContentSize().height - 10
    );
    if (direction) {
        rect.origin.x -= 40;
    } else {
        rect.origin.x += 40;
    }
    this->attackRect = AttackRect(rect, power, false);
}

void Hero::handBlade() {
    if (isInTheAir()) {
        if (getMode() == HeroMode::LIGHTBLADE) {
            setMode(HeroMode::SHIELD);
        } else
            setMode(HeroMode::LIGHTBLADE);
    } else {
        if (getMode() == HeroMode::LIGHTBLADE) {
            armature->getAnimation()->play("Stand");
            setMode(HeroMode::SHIELD);
        } else {
            setState(EntityState::FORCED);
            armature->getAnimation()->playByIndex(13);
            AudioEngine::play2d("Audio/haaaaa.mp3");
            scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterHandBlade), 1.0f);
        }
    }
}

void Hero::afterHandBlade(float dt) {
    setMode(HeroMode::LIGHTBLADE);
    setState(EntityState::NORMAL);
    armature->getAnimation()->playByIndex(18);
    armature->setOpacity(255);
    armature->setColor(Color3B(255, 255, 255));
}

void Hero::jump() {
    if (!isInTheAir()) {
        if (getMode() == HeroMode::LIGHTBLADE) {
            armature->getAnimation()->play("SB_Jump");
        } else
            armature->getAnimation()->play("Jump");
        this->scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::doJump), 0.33f);
    }
}

void Hero::doJump(float dt) {
    int temp = static_cast<int>(getPositionY());
    if (getMode() == HeroMode::LIGHTBLADE) {
        armature->getAnimation()->play("SB_Up");
    } else
        armature->getAnimation()->play("Up");
    setState(EntityState::NORMAL);
    setPositionY(temp + 10);
    // initRigidbody();
}

void Hero::modeShield() {
    setMode(HeroMode::SHIELD);
    setState(EntityState::NORMAL);
    armature->setOpacity(255);
    armature->setColor(Color3B(255, 255, 255));
    AudioEngine::play2d("Audio/maxArmor.mp3");
    armature->getAnimation()->play("Stand");
}

void Hero::modeIvisible() {
    if (isInTheAir()) {
        setMode(HeroMode::INVISIBLE);
        scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterModeIvisible), 0.6f);
    } else {
        if (getMode() != HeroMode::INVISIBLE) {
            setState(EntityState::FORCED);
            armature->getAnimation()->play("ModeChange");
            AudioEngine::play2d("Audio/Cloak.mp3");
            scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterModeIvisible), 0.6f);
        }
    }
}

void Hero::afterModeIvisible(float dt) {
    setMode(HeroMode::INVISIBLE);
    setState(EntityState::NORMAL);
    armature->setOpacity(50);
    armature->setColor(Color3B(0, 0, 200));
    armature->getAnimation()->play("Stand");
}

void Hero::modeClockUp() {
    if (isInTheAir()) {
        setMode(HeroMode::CLOCKUP);
        scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterModeClockUp), 0.6f);
    } else {
        if (getMode() != HeroMode::CLOCKUP) {
            setState(EntityState::FORCED);
            armature->getAnimation()->play("ModeChange");
            AudioEngine::play2d("Audio/Clock.mp3");
            scheduleOnce(AX_SCHEDULE_SELECTOR(Hero::afterModeClockUp), 0.6f);
        }
    }
}

void Hero::afterModeClockUp(float dt) {
    setMode(HeroMode::CLOCKUP);
    setState(EntityState::NORMAL);
    armature->setColor(Color3B(30, 255, 40));
    armature->setOpacity(255);
    armature->getAnimation()->play("Stand");
}

void Hero::update(float dt) {
    Entity::update(dt);
    updateStatus();

    switch (state) {
        case EntityState::WALKING:
            updateWalk(dt);
            break;
        case EntityState::NORMAL:
            updateIdle(dt);
            break;
        default:
            break;
    }
}

void Hero::switchToIdle() {
    state = EntityState::NORMAL;
    getArmature()->getAnimation()->play("Stand");
    rigidBody.getVelocity().x = 0;
}

void Hero::switchToWalk() {
    state = EntityState::WALKING;
    CCLOG("Play Walk");
    getArmature()->getAnimation()->play("Walk");
}

void Hero::updateWalk(float delta) {
    const auto input = InputManager::getInstance();
    if (input->isKeyPressed(InputManager::Keys::DPAD_RIGHT)) {
        rigidBody.getVelocity().x = moveSpeed;
        setDirection(RIGHT);
    } else if (input->isKeyPressed(InputManager::Keys::DPAD_LEFT)) {
        rigidBody.getVelocity().x = -moveSpeed;
        setDirection(LEFT);
    } else {
        switchToIdle();
    }
}

void Hero::updateIdle(float dt) {
    const auto input = InputManager::getInstance();
    if (input->isKeyPressed(InputManager::Keys::DPAD_RIGHT)) {
        switchToWalk();
    } else if (input->isKeyPressed(InputManager::Keys::DPAD_LEFT)) {
        switchToWalk();
    }
}

void Hero::updateStatus() {
    // 主角的状态设置
    if (this->sp > 0) {
        if (this->getMode() == HeroMode::INVISIBLE) {
            this->sp -= 0.2f;
        } else if (this->getMode() == HeroMode::CLOCKUP) {
            this->sp -= 0.1f;
        } else if (this->getMode() == HeroMode::LIGHTBLADE) {
            this->sp -= 0.1f;
        } else {
            this->sp += 0.1f;
        }
    } else {
        this->modeShield();
        this->sp += 1;
    }
    if (this->tp < 100) {
        this->tp += 0.07f;
    } else {
        this->hp = 100;
        this->sp = 100;
        this->tp = 0;
    }
    if (this->hp < 0) {
        this->hp = 0;
    }
    if (this->hp > 100) {
        this->hp = 100;
    }
    if (this->sp < 0) {
        this->sp = 0;
    }
    if (this->sp > 100) {
        this->sp = 100;
    }
    if (this->tp < 0) {
        this->tp = 0;
    }
    if (this->tp > 100) {
        this->tp = 100;
    }
}
