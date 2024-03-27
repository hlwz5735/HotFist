#include "Entity.h"

USING_NS_AX;
using namespace cocostudio;

Entity::Entity(): armature(nullptr),
                  power(0),
                  direction(LEFT),
                  moveSpeed(100.f),
                  jumpAbility(120),
                  state(EntityState::NORMAL),
                  hp(0), sp(0) {
}

bool Entity::init() {
    if (!Node::init()) {
        return false;
    }
    initSprite();
    return true;
}

void Entity::initSprite() {
    if (armature != nullptr) {
        animation = armature->getAnimation();
    }
}

void Entity::initPhysicsBody(const ax::Vec2 &size, const ax::Vec2 &offset) {
    //const auto realOffset = Vec2(size.x / 2, size.y / 2) + offset;
    //const auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(1, 0, 1), realOffset);
    //physicsBody->setDynamic(true);
    //physicsBody->setRotationEnable(false);
    //setPhysicsBody(physicsBody);
}

void Entity::update(float dt) {
    Node::update(dt);
    grounded = false;
    //_physicsBody->getWorld()->rayCast([this](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data) {
    //    if (info.shape->getBody() == _physicsBody) {
    //        return false;
    //    }
    //    grounded = true;
    //    return true;
    //}, getPosition(), getPosition() + Vec2(0, 1), nullptr);

    switch (state) {
    case EntityState::WALKING:
        updateWalk(dt);
        break;
    case EntityState::NORMAL:
        updateIdle(dt);
        break;
    case EntityState::JUMPING:
        updateJump(dt);
        break;
    default:
        break;
    }
}

void Entity::switchToIdle() {
    if (state == EntityState::NORMAL) {
        return;
    }
    state = EntityState::NORMAL;
    animation->play("Stand");
    const auto v = _physicsBody->getVelocity();
    _physicsBody->setVelocity(Vec2(0, v.y));
}

void Entity::updateIdle(float delta) {
}


void Entity::switchToWalk() {
    if (state == EntityState::WALKING) {
        return;
    }
    state = EntityState::WALKING;
    animation->play("Walk");
}


void Entity::updateWalk(float delta) {
    const auto vx = static_cast<int>(direction) * moveSpeed;
    const auto v = _physicsBody->getVelocity();
    _physicsBody->setVelocity(Vec2(vx, v.y));
}

void Entity::switchToJump() {
    state = EntityState::ATTACKING;
    animation->play("Jump");
    this->scheduleOnce(AX_SCHEDULE_SELECTOR(Entity::doJump), 0.17f);
}

void Entity::updateJump(float delta) {
    if (grounded) {
        switchToIdle();
    }
}

void Entity::jump() {
    if (grounded && (state == EntityState::NORMAL || state == EntityState::WALKING)) {
        switchToJump();
    }
}

void Entity::doJump(float dt) {
    animation->play("Up");
    const auto v = _physicsBody->getVelocity();
    _physicsBody->setVelocity(Vec2(v.x, jumpAbility));
    state = EntityState::JUMPING;
}

void Entity::hurt() {
    setState(EntityState::HURT);
    // 浮空的话就出浮空受伤
    if (!grounded) {
        airHurt();
    } else {
        float tempRand = AXRANDOM_0_1();
        // 在头部受伤和腹部受伤之间随机出一个
        if (tempRand < 0.5f) {
            headHurt();
        } else {
            flankHurt();
        }
    }
}

//下面三个函数在不同的子类里有不同的实现，这里的三个只是卖萌
void Entity::headHurt() {
    CCLOG("Oh,my head!\n");
    setState(EntityState::NORMAL);
}

void Entity::flankHurt() {
    CCLOG("Oh,my baby!\n");
    setState(EntityState::NORMAL);
}

void Entity::airHurt() {
    CCLOG("I want to fly so high\n");
    setState(EntityState::NORMAL);
}

void Entity::refresh(float dt) {
    this->setState(EntityState::NORMAL);
    attackRect.setFinished(true);
    armature->getAnimation()->play("Stand");
}

void Entity::setDirection(Direction dir) {
    direction = dir;
    armature->setScaleX(dir);
}
