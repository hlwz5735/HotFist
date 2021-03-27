#include "cocostudio/CCArmature.h"
#include "PhysicsDebugScene.h"
#include "../readers/LevelDataReader.h"

bool PhysicsDebugScene::init()
{
    if (!Scene::init())
        return false;
    if (!initWithPhysics())
    {
        return false;
    }

    auto layer = Layer::create();

    const auto defaultPhysicsMaterial = PhysicsMaterial(1, 0, 1);
    // 1单位 -> 10cm
    this->getPhysicsWorld()->setGravity(Vec2(0.0f, -198.0f));
    this->getPhysicsWorld()->setDebugDrawMask(0xffffffff);

    this->levelData = LevelDataReader::readDocument("Levels/level_01.json");
    auto map = TMXTiledMap::create(this->levelData.getTmxMap());
    if (map != nullptr)
    {
        map->setPosition(Point::ZERO);
        layer->addChild(map, 0);
        auto objGroup = map->getObjectGroup("groundRect");

        for (auto iter = objGroup->getObjects().begin(); iter != objGroup->getObjects().end(); iter++)
        {
            auto blockRect = iter->asValueMap();
            float tempX = blockRect["x"].asFloat();
            float tempY = blockRect["y"].asFloat();
            float tempWidth = blockRect["width"].asFloat();
            float tempHeight = blockRect["height"].asFloat();

            const auto node = Node::create();
            const auto physicsBox = PhysicsBody::createBox(Size(tempWidth, tempHeight), defaultPhysicsMaterial);
            physicsBox->setDynamic(false);
            node->addComponent(physicsBox);
            node->setPosition(tempX + tempWidth / 2, tempY + tempHeight / 2);
            layer->addChild(node);
        }
    }

    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("Nivida0.png", "Nivida0.plist", "Nivida.ExportJson");
    //新的主角精灵
    cocostudio::Armature* sprite = cocostudio::Armature::create("Nivida");
    // 设置当前运行动画的索引，一个“工程”可以建立多个动画
    sprite->getAnimation()->play("Stand");
    sprite->setPosition(120, 300 - sprite->getContentSize().height / 2);

    const auto contentSize = sprite->getContentSize();
    auto physicsBody = PhysicsBody::createBox(
            contentSize, defaultPhysicsMaterial, Vec2(-contentSize.width / 2, 0));
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    sprite->addComponent(physicsBody);

    layer->addChild(sprite);
    layer->setPosition(Vec2::ZERO);
    this->addChild(layer);

    return true;
}
