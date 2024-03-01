//
// Created by 厉猛 on 2020/4/22.
//

#ifndef HOTFISTREMASTER_ENEMYDATA_H
#define HOTFISTREMASTER_ENEMYDATA_H

#include "math/Vec2.h"

using namespace std;
USING_NS_AX;

class EnemyData
{
public:
    const string &getType() const;

    void setType(const string &type);

    const Point &getPosition() const;

    void setPosition(const Point &position);

private:
    /** 敌人类型 */
    string type;
    /** 敌人位置 */
    Point position;
};


#endif //HOTFISTREMASTER_ENEMYDATA_H
