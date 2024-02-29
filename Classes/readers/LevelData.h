//
// Created by 厉猛 on 2020/4/22.
//

#ifndef HOTFISTREMASTER_LEVELDATA_H
#define HOTFISTREMASTER_LEVELDATA_H

#include "../EnemyData.h"

using std::string;
using namespace ax;

class LevelData
{
public:
    const string &getName() const;

    void setName(const string &name);

    float getWidth() const;

    void setWidth(float width);

    const Point &getStartPosition() const;

    void setStartPosition(const Point &startPosition);

    const string &getTmxMap() const;

    void setTmxMap(const string &tmxMap);

    vector<EnemyData> &getEnemies();

    void setEnemies(const vector<EnemyData> &enemies);

    const string &getBgm() const;

    void setBgm(const string &bgm);

private:
    /** 关卡名 */
    string name;
    /** 关卡宽度 */
    float width;
    /** 初始位置 */
    Point startPosition;
    /** 对应地图文件路径 */
    string tmxMap;
    /** 对应背景音乐路径 */
    string bgm;
    /** 敌人数据列表 */
    vector<EnemyData> enemies;
};


#endif //HOTFISTREMASTER_LEVELDATA_H
