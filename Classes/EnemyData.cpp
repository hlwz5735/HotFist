//
// Created by 厉猛 on 2020/4/22.
//

#include "EnemyData.h"

const string &EnemyData::getType() const
{
    return type;
}

void EnemyData::setType(const string &type)
{
    EnemyData::type = type;
}

const Point &EnemyData::getPosition() const
{
    return position;
}

void EnemyData::setPosition(const Point &position)
{
    EnemyData::position = position;
}
