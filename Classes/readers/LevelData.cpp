//
// Created by 厉猛 on 2020/4/22.
//

#include "LevelData.h"

const string &LevelData::getName() const
{
    return name;
}

void LevelData::setName(const string &name)
{
    LevelData::name = name;
}

float LevelData::getWidth() const
{
    return width;
}

void LevelData::setWidth(float width)
{
    LevelData::width = width;
}

const Point &LevelData::getStartPosition() const
{
    return startPosition;
}

void LevelData::setStartPosition(const Point &startPosition)
{
    LevelData::startPosition = startPosition;
}

const string &LevelData::getTmxMap() const
{
    return tmxMap;
}

void LevelData::setTmxMap(const string &tmxMap)
{
    LevelData::tmxMap = tmxMap;
}

vector<EnemyData> &LevelData::getEnemies()
{
    return enemies;
}

void LevelData::setEnemies(const vector<EnemyData> &enemies)
{
    LevelData::enemies = enemies;
}

const string &LevelData::getBgm() const
{
    return bgm;
}

void LevelData::setBgm(const string &bgm)
{
    LevelData::bgm = bgm;
}
