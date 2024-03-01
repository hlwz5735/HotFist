//
// Created by 厉猛 on 2024-02-29.
//

#include <algorithm>
#include "Global.h"
#include "RigidBody.h"
#include "../gameplay/GameLayer.h"

USING_NS_AX;

const auto gravity = Vec2(0, -PHYSICS_GRAVITY);

/// 计算两矩形的相交矩形
Rect intercectRect(const Rect &r1, const Rect &r2) {
    auto x1 = std::max(r1.getMinX(), r2.getMinX());
    auto y1 = std::max(r1.getMinY(), r2.getMinY());
    auto x2 = std::min(r1.getMaxX(), r2.getMaxX());
    auto y2 = std::min(r1.getMaxY(), r2.getMaxY());
    return {
        x1,
        y1,
        x2 - x1,
        y2 - y1
    };
}

/// 计算两矩形中心点的差，作为反推力的方向矢量
Vec2 centerPointDiff(const Rect &r1, const Rect &r2) {
    return { r2.getMidX() - r1.getMidX(), r2.getMidY() - r1.getMidY() };
}

RigidBody::RigidBody(): grounded(false), parent(nullptr), world(nullptr) {
}

void RigidBody::update(float delta) {
    if (!parent || !world) {
        return;
    }

    velocity += realForce();
    auto destPos = parent->getPosition() + velocity;
    auto destBody = Rect(
        destPos.x + body.origin.x,
        destPos.y + body.origin.y,
        body.size.width, body.size.height
    );

    // 各种修正计算...
    const auto &blockList = world->getStaticBlockVector();
    for (const auto & i : blockList) {
        if (destBody.intersectsRect(i)) {
            destPos = doCompensation(destBody, i);
            destBody = Rect(
                destPos.x + body.origin.x,
                destPos.y + body.origin.y,
                body.size.width, body.size.height
            );
        }
    }

    parent->setPosition(destPos);
    realBody = destBody;
}

Vec2 RigidBody::realForce() {
    return force + gravity;
}

Vec2 RigidBody::doCompensation(const Rect &destBody, const Rect &staticBlock) {
    auto intersect = intercectRect(destBody, staticBlock);
    auto compensationVec = centerPointDiff(destBody, intersect);
    if (compensationVec.x != 0) {
        this->velocity.x = 0;
    }
    if (compensationVec.y != 0) {
        this->velocity.y = 0;
    }
    return parent->getPosition() + velocity;
}
