//
// Created by 厉猛 on 2024-02-29.
//

#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "cocos2d.h"

class GameLayer;

/// 刚体盒子对象，受世界物理体系影响
class RigidBody {
public:
    RigidBody();

    virtual void update(float delta);

    ax::Vec2 realForce();


    void addForce(const ax::Vec2 &f) { force += f; }

    void bind(ax::Node *p) { parent = p; }
    void addToWorld(GameLayer *world) { this->world = world; }

    void setForce(const ax::Vec2 &newForce) { force = newForce; }
    ax::Vec2 &getForce() { return force; }
    void setVelocity(const ax::Vec2 &newVelocity) { velocity = newVelocity; }
    void setVelocity(float x, float y) { velocity = ax::Vec2(x, y); }
    ax::Vec2 &getVelocity() { return velocity; }
    void setBody(const ax::Rect &body) { this->body = body; }
    const ax::Rect &getBody() const { return body; }
    const ax::Rect &getRealBody() const { return realBody; }
    bool isGrounded() const { return grounded; }
private:
    ax::Vec2 doCompensation(const ax::Rect &destBody, const ax::Rect &staticBlock);

    ax::Vec2 force;
    ax::Vec2 velocity;
    ax::Rect body;
    ax::Rect realBody;
    /** 脚踏地面的标记 */
    bool grounded;

    ax::Node *parent;
    GameLayer *world;
};



#endif //RIGIDBODY_HPP
