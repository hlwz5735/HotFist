#include "cocostudio/Armature.h"
#include "PhysicsDebugScene.h"
#include "../readers/LevelDataReader.h"
#include "entity/Hero.h"
#include "gameplay/ControlLayer.h"

// 1单位 = 100cm
constexpr int PTM_RATIO = 100;

bool PhysicsDebugScene::init() {
    if (!Scene::init()) {
        return false;
    }
    initBox2dWorld();

    auto layer = Layer::create();

    this->levelData = LevelDataReader::readDocument("Levels/level_01.json");
    auto map = TMXTiledMap::create(this->levelData.getTmxMap());
    if (map != nullptr) {
        map->setPosition(Point::ZERO);
        layer->addChild(map, 0);

        auto objGroup = map->getObjectGroup("groundRect");
        for (auto &rectObj : objGroup->getObjects()) {
            auto blockRect = rectObj.asValueMap();
            const float tempX = blockRect["x"].asFloat();
            const float tempY = blockRect["y"].asFloat();
            const float halfWidth = blockRect["width"].asFloat() / 2;
            const float halfHeight = blockRect["height"].asFloat() / 2;

            b2BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set((tempX + halfWidth) / PTM_RATIO, (tempY + halfHeight) / PTM_RATIO);
            const auto body = world->CreateBody(&bodyDef);
            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(halfWidth / PTM_RATIO, halfHeight / PTM_RATIO);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.3f;
            body->CreateFixture(&fixtureDef);
        }
    }

    const auto hero = Hero::create();
    hero->scheduleUpdate();
    hero->setPosition(120, 150);
    layer->addChild(hero);
    layer->setPosition(Vec2::ZERO);

    this->addChild(layer);

    const auto controllerLayer = ControlLayer::create();
    this->addChild(controllerLayer);
    controllerLayer->setHero(hero);

    this->scheduleUpdate();
    return true;
}

void PhysicsDebugScene::update(float delta) {
    Scene::update(delta);

    // https://gafferongames.com/post/fix_your_timestep/
    constexpr int velocityIterations = 8;
    constexpr int positionIterations = 1;

    world->Step(delta, velocityIterations, positionIterations);

    // Debug draw
    drawBox2D->clear();
    world->DebugDraw();
}

void PhysicsDebugScene::initBox2dWorld() {
    world = new b2World(b2Vec2(0, -10));
    world->SetAllowSleeping(true);
    world->SetContinuousPhysics(true);

    uint32 flags = 0;
    flags += 1 * b2Draw::e_shapeBit;
    flags += 1 * b2Draw::e_jointBit;
    flags += 0 * b2Draw::e_aabbBit;
    flags += 0 * b2Draw::e_centerOfMassBit;
    debugDraw.SetFlags(flags);
    debugDraw.mRatio = PTM_RATIO;
    debugDraw.debugNodeOffset = { 0, 0 };
    world->SetDebugDraw(&debugDraw);
    drawBox2D = debugDraw.GetDrawNode();
    addChild(drawBox2D, 100);
    drawBox2D->setOpacity(150);
}
