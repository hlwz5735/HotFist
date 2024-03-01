#include "audio/AudioEngine.h"
#include "cocostudio/Armature.h"
#include "GameLayer.h"

#include "InputManager.h"
#include "../readers/LevelDataReader.h"
#include "../entity/Hero.h"
#include "../entity/JapanArmyI.h"
#include "../entity/JapanArmyII.h"
#include "../entity/Liuhai.h"
#include "../entity/Ninja.h"
#include "SceneFactory.h"

USING_NS_AX;

GameLayer::GameLayer(): hero(nullptr), tileCountX(0), tileCountY(0), map(nullptr) {
}

bool GameLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    InputManager::getInstance()->reset();
    this->scheduleUpdate();

#if defined(DebugDrawRects)
    this->drawNode = DrawNode::create();
    this->addChild(drawNode, 100);
    drawNode->setPosition(0, 0);
#endif
    return true;
}

void GameLayer::loadData(const std::string &jsonPath) {
    this->levelData = LevelDataReader::readDocument(jsonPath);
    this->stageSize = Size(static_cast<int>(this->levelData.getWidth()), 1000);

    AudioEngine::stopAll();
    AudioEngine::play2d(levelData.getBgm(), true);

    this->initMap();
    this->initEnemyArr();

    hero = Hero::create();
    hero->setPosition(this->levelData.getStartPosition());
    hero->getRigidBody().addToWorld(this);
    this->addChild(hero, 10);
}

void GameLayer::update(float dt) {
    InputManager::getInstance()->update();
    updatePhysicsWorld(dt);
    hero->update(dt);
    for (auto enemy: enemyArr) {
        enemy->update(dt);
    }
    updateCamera();

    if (this->gameFinished) {
        return;
    }
    // if (hero->getPositionX() >= this->stageSize.width) {
    //     this->gameFinished = true;
    //     Scene *scene = SceneFactory::story02();
    //     _director->replaceScene(TransitionFade::create(2.0f, scene));
    // }
    if (hero->getHp() <= 0) {
        hero->setState(Entity::EntityState::FORCED);
        hero->getArmature()->getAnimation()->play("Fly");
        // if (hero->getFaceTo()) {
        //     hero->setVelocityX(5);
        // } else {
        //     hero->setVelocityX(-5);
        // }
        Scene *scene = SceneFactory::gameOverScene();
        _director->replaceScene(TransitionFade::create(2.0f, scene));
        this->gameFinished = true;
    }
#if defined(DebugDrawRects)
    this->updateDebugDraw();
#endif
}

void GameLayer::initMap() {
    map = TMXTiledMap::create(this->levelData.getTmxMap());
    if (map != nullptr) {
        map->setPosition(Point::ZERO);
        this->addChild(map, 0);
        initGroundRect();
    }
}

void GameLayer::initGroundRect() {
    auto objGroup = map->getObjectGroup("groundRect");

    for (auto &iter : objGroup->getObjects()) {
        auto blockRect = iter.asValueMap();
        float tempX = blockRect["x"].asFloat();
        float tempY = blockRect["y"].asFloat();
        float tempWidth = blockRect["width"].asFloat();
        float tempHeight = blockRect["height"].asFloat();
        this->staticBlockVector.emplace_back(tempX, tempY, tempWidth, tempHeight);
    }
}

void GameLayer::initEnemyArr() {
    auto &enemyDataList = this->levelData.getEnemies();

    for (auto &enemyData: enemyDataList) {
        Enemy *pEnemy;

        const auto type = enemyData.getType();
        if (type == "JapanArmyII") {
            pEnemy = JapanArmyII::create();
        } else if (type == "Liuhai") {
            pEnemy = Liuhai::create();
        } else if (type == "Ninja") {
            pEnemy = Ninja::create();
        } else {
            pEnemy = JapanArmyI::create();
        }

        pEnemy->setPosition(enemyData.getPosition());
        pEnemy->getRigidBody().addToWorld(this);
        this->addChild(pEnemy, 5);
        this->enemyArr.pushBack(pEnemy);
    }
}

void GameLayer::updatePhysicsWorld(float delta) {
    auto &rb = hero->getRigidBody();
    rb.update(delta);
    for (auto &enemy : enemyArr) {
        auto &rigidbody = enemy->getRigidBody();
        rigidbody.update(delta);
    }
}

void GameLayer::updateAI() {
    // for (auto pTemp: this->enemyArr) {
    //     float heroX = hero->getPositionX();
    //     //thisX 是当前怪物的X坐标
    //     float thisX = pTemp->getPositionX();
    //     float thisY = pTemp->getPositionY();
    //
    //     //如果当前为待机状态，那么让它变为巡逻状态
    //     if (pTemp->enemyState == Enemy::EnemyState::STADINGBY) {
    //         //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //         pTemp->enemyState = Enemy::EnemyState::PATROLING;
    //         pTemp->patrol();
    //     } ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //     //如果在巡逻状态，那么开始判断是业内有木有主角，如果有，变为reaching
    //     else if (pTemp->enemyState == Enemy::EnemyState::PATROLING) {
    //         //{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
    //         //视野矩形和主角碰撞矩形发生碰撞，也就是敌人“看到了”主角
    //         if (pTemp->m_ViewRect.intersectsRect(hero->getRigidRect()) && hero->getMode() != Hero::HeroMode::INVISIBLE) {
    //             pTemp->enemyState = Enemy::EnemyState::REACHING;
    //         } else
    //             pTemp->patrol();
    //     } //}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
    //     else if (pTemp->enemyState == Enemy::EnemyState::REACHING) {
    //         //{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
    //         if (pTemp->m_ViewRect.intersectsRect(hero->getRigidRect())) {
    //             if (heroX - thisX >= 40) {
    //                 if (hero->getPositionY() - thisY > 12 && heroX - thisX < 80) {
    //                     pTemp->jump();
    //                 }
    //                 pTemp->setDirection(false);
    //                 pTemp->run();
    //             } else if (heroX - thisX <= -40) {
    //                 if (hero->getPositionY() - thisY > 12 && heroX - thisX > -80) {
    //                     pTemp->jump();
    //                 }
    //                 pTemp->setDirection(true);
    //                 pTemp->run();
    //             } else {
    //                 int tempRand = static_cast<int>(AXRANDOM_0_1() * 100);
    //                 if (tempRand > 90) {
    //                     pTemp->attack();
    //                 } else {
    //                     pTemp->enemyState = Enemy::EnemyState::STADINGBY;
    //                 }
    //             }
    //         }
    //         //从碰撞框中消失，也就是看不到主角了
    //         else {
    //             pTemp->enemyState = Enemy::EnemyState::PATROLING;
    //         }
    //
    //         if (hero->getMode() == Hero::HeroMode::INVISIBLE) {
    //             pTemp->enemyState = Enemy::EnemyState::PATROLING;
    //         }
    //     } //}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
    //     /*********************************中间有待完善************************************/
    //     pTemp->initViewRect();
    // }
}

void GameLayer::updateHero() {
    // hero->inTheAirFlag = true;
    // for (auto tempBlock: this->staticBlockVector) {
    //     //一旦发生碰撞，就将flag标记记为true，同时退出循环，
    //     if (hero->getRect().intersectsRect(tempBlock)) {
    //         //对是否站在当前矩形的判断
    //         if (hero->getRect().getMinY() - tempBlock.getMaxY() > -16
    //             && hero->getRect().getMinY() - tempBlock.getMaxY() <= 0) {
    //             hero->inTheAirFlag = false;
    //             hero->setPositionY(tempBlock.getMaxY());
    //             hero->velocityY = 0;
    //             hero->initBlock();
    //             if (!hero->jumpMainFlag) {
    //                 if (hero->getMode() == Hero::HeroMode::LIGHTBLADE)
    //                     hero->m_sprite->getAnimation()->play("SB_Stand");
    //                 else
    //                     hero->m_sprite->getAnimation()->play("Stand");
    //                 hero->velocityX = 0;
    //                 hero->jumpMainFlag = true;
    //             }
    //         } else if (hero->getRect().getMaxY() - tempBlock.getMinY() < 16
    //                    && hero->getRect().getMaxY() - tempBlock.getMinY() >= 0) {
    //             hero->velocityY = -3;
    //         }
    //         // 如果是X方向的碰撞，那么就阻挡玩家移动（将坐标回移两个像素）
    //         else {
    //             float tempX = hero->getPositionX();
    //             if (hero->getMode() != Hero::HeroMode::CLOCKUP) {
    //                 //如果角色朝左
    //                 if (hero->faceto)
    //                     hero->setPositionX(tempX - hero->velocityX + 1);
    //                 else {
    //                     hero->setPositionX(tempX - hero->velocityX - 1);
    //                 }
    //             } else {
    //                 //如果角色朝左
    //                 if (hero->faceto)
    //                     hero->setPositionX(tempX - hero->velocityX + 1);
    //                 else {
    //                     hero->setPositionX(tempX - hero->velocityX - 1);
    //                 }
    //             }
    //             break;
    //         }
    //     } //判断是否碰撞的if结束
    // } //循环判断结束
    // if (hero->inTheAirFlag) {
    //     int temp = static_cast<int>(hero->getPositionY());
    //     if (hero->velocityY > -maxVelocityY)
    //         hero->velocityY -= GRAVITY;
    //     hero->setPositionY(temp + hero->velocityY);
    // }
    // int temp = static_cast<int>(hero->getPositionX());
    // hero->setPositionX(temp + hero->velocityX);
    // hero->initBlock();
}

void GameLayer::updateEnemy() {
    // bool isAttackFinished = false;
    // for (auto it = enemyArr.begin(); it != enemyArr.end();) {
    //     auto pTemp = *it;
    //     pTemp->inTheAirFlag = true;
    //     for (auto tempBlock: this->staticBlockVector) {
    //         if (pTemp->getPositionX() >= this->stageSize.width) {
    //             pTemp->setDirection(true);
    //             pTemp->setPositionX(pTemp->getPositionX() - 5);
    //         }
    //         //一旦发生碰撞，就将flag标记，同时退出循环，
    //         if (pTemp->getRect().intersectsRect(tempBlock)) {
    //             //对是否站在当前矩形的判断
    //             if (pTemp->getRect().getMinY() - tempBlock.getMaxY() > -16
    //                 && pTemp->getRect().getMinY() - tempBlock.getMaxY() <= 0) {
    //                 pTemp->inTheAirFlag = false;
    //                 pTemp->setPositionY(tempBlock.getMaxY());
    //                 pTemp->velocityY = 0;
    //                 pTemp->initBlock();
    //                 if (!pTemp->jumpMainFlag) {
    //                     pTemp->m_sprite->getAnimation()->play("Stand");
    //                     pTemp->jumpMainFlag = true;
    //                 }
    //             } else if (pTemp->getRect().getMaxY() - tempBlock.getMinY() < 16
    //                        && pTemp->getRect().getMaxY() - tempBlock.getMinY() >= 0) {
    //                 pTemp->velocityY = -3;
    //             }
    //             //如果是X方向的碰撞，那么就阻挡玩家移动（将坐标回移两个像素），之后转向
    //             else {
    //                 //如果角色朝左
    //                 if (pTemp->velocityX < 0) {
    //                     pTemp->velocityX = -pTemp->velocityX;
    //                     float temp = AXRANDOM_0_1() * 100;
    //                     if (temp > 70) {
    //                         pTemp->jump();
    //                     } else {
    //                         if (pTemp->enemyState != Enemy::EnemyState::DYING) {
    //                             pTemp->changeDirection();
    //                         }
    //                     }
    //                     pTemp->initViewRect();
    //                 } else if (pTemp->velocityX > 0) {
    //                     pTemp->velocityX = -pTemp->velocityX;
    //                     float temp = AXRANDOM_0_1() * 100;
    //                     if (temp > 70) {
    //                         pTemp->jump();
    //                     } else {
    //                         pTemp->changeDirection();
    //                     }
    //                     pTemp->initViewRect();
    //                 }
    //                 break;
    //             }
    //         } //判断是否碰撞的if结束
    //     } //循环判断结束
    //     if (pTemp->inTheAirFlag) {
    //         int temp = static_cast<int>(pTemp->getPositionY());
    //         if (pTemp->velocityY > -maxVelocityY)
    //             pTemp->velocityY -= GRAVITY;
    //         pTemp->setPositionY(temp + pTemp->velocityY);
    //     }
    //     int temp = static_cast<int>(pTemp->getPositionX());
    //     pTemp->setPositionX(temp + pTemp->velocityX);
    //     pTemp->initBlock();
    //     //攻击与受伤的判断
    //     if (hero->getRect().intersectsRect(pTemp->m_attack) && !pTemp->m_attack.isFinished) {
    //         hero->hurt();
    //         if (hero->getMode() == Hero::HeroMode::SHIELD) {
    //             hero->hp -= (pTemp->m_attack.m_force * 0.6f);
    //         } else
    //             hero->hp -= pTemp->m_attack.m_force;
    //         pTemp->m_attack.isFinished = true;
    //     }
    //     if (pTemp->m_block.intersectsRect(hero->m_attack) && !hero->m_attack.isFinished) {
    //         pTemp->hurt();
    //         pTemp->hp -= hero->m_attack.m_force;
    //         isAttackFinished = true;
    //     }
    //     if (pTemp->hp <= 0) {
    //         pTemp->setState(Entity::EntityState::FORCED);
    //         pTemp->enemyState = Enemy::EnemyState::DYING;
    //         pTemp->m_block = Rect(-1, -1, 1, 1);
    //         pTemp->m_sprite->getAnimation()->play("Fly");
    //         if (pTemp->faceto) {
    //             pTemp->velocityX = 5;
    //         } else {
    //             pTemp->velocityX = -5;
    //         }
    //     }
    //
    //     // 移除超出舞台的敌人
    //     if (pTemp->getPositionX() < -100 || pTemp->getPositionX() > this->stageSize.width + 100) {
    //         it = enemyArr.erase(it);
    //         this->removeChild(pTemp);
    //     } else {
    //         it++;
    //     }
    // }
    // if (isAttackFinished) {
    //     hero->getAttackRect().isFinished = true;
    // }
}

void GameLayer::updateCamera() {
    const Size mapTiledNum = map->getMapSize();
    const Size tiledSize = map->getTileSize();
    const Size mapSize = Size(mapTiledNum.width * tiledSize.width, mapTiledNum.height * tiledSize.height);
    const Size visibleSize = _director->getVisibleSize();
    // 屏幕中点
    const Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

    // 主角的坐标
    const Point spritePos = this->hero->getPosition();

    // 如果主角的坐标小于屏幕的一半，则取屏幕中点坐标，否则取主角的坐标
    float x = std::max(spritePos.x, centerPos.x);
    float y = std::max(spritePos.y, centerPos.y);
    // 如果X、Y的坐标大于右上角的极限值，则取不让地图超出屏幕造成出现黑边的极限坐标
    x = std::min(x, mapSize.width - centerPos.x);
    y = std::min(y, mapSize.height - centerPos.y);

    this->setPosition(centerPos - Point(x, y));
}

#if defined(DebugDrawRects)
void extractRect(const Rect &rect, Point *pArr) {
    pArr[0] = Point(rect.getMinX(), rect.getMinY());
    pArr[1] = Point(rect.getMaxX(), rect.getMinY());
    pArr[2] = Point(rect.getMaxX(), rect.getMaxY());
    pArr[3] = Point(rect.getMinX(), rect.getMaxY());
}

static void drawRect(DrawNode *drawNode, const Rect &rect, const Color3B &color, float alpha = 0.1f) {
    Point pointArr[4];
    extractRect(rect, pointArr);
    drawNode->drawPolygon(pointArr, 4, Color4F(color, alpha), 1, Color4F(color, 1));
}

void GameLayer::updateDebugDraw() {
    const auto rigidbodyColor = Color3B::GRAY;
    const auto staticBlockColor = Color3B::GREEN;
    const auto attackColor = Color3B(255, 0, 0);
    const auto finishedAttackColor = Color3B(100, 0, 0);
    const auto enemyAttackColor = Color3B::ORANGE;
    const auto enemyFinishedAttackColor = Color3B(100, 50, 0);

    this->drawNode->clear();

    for (auto &rect: this->staticBlockVector) {
        drawRect(drawNode, rect, staticBlockColor);
    }

    drawRect(drawNode, hero->getRigidBody().getRealBody(), rigidbodyColor);
    drawRect(drawNode, hero->getAttackRect(), hero->getAttackRect().isFinished() ? finishedAttackColor : attackColor);
    for (Enemy *pEnemy: enemyArr) {
        drawRect(drawNode, pEnemy->getRigidBody().getRealBody(), rigidbodyColor);
        const auto &enemyAttackRect = pEnemy->getAttackRect();
        drawRect(drawNode, enemyAttackRect, enemyAttackRect.isFinished() ? enemyFinishedAttackColor : enemyAttackColor);
    }
}
#endif
