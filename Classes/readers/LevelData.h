//
// Created by 厉猛 on 2020/4/22.
//

#ifndef HOTFISTREMASTER_LEVELDATA_H
#define HOTFISTREMASTER_LEVELDATA_H

#include "../EnemyData.h"

using std::string;
USING_NS_AX;

class LevelData {
public:
    LevelData();

    const string &getName() const { return name; }
    void setName(const string &name) { this->name = name; }
    float getWidth() const { return width; }
    void setWidth(float width) { this->width = width; }
    const Point &getStartPosition() const { return startPosition; }
    void setStartPosition(const Point &startPosition) { this->startPosition = startPosition; }
    const string &getTmxMap() const { return tmxMap; }
    void setTmxMap(const string &tmxMap) { this->tmxMap = tmxMap; }
    vector<EnemyData> &getEnemies() { return enemies; }
    void setEnemies(const vector<EnemyData> &enemies) { this->enemies = enemies; }
    const string &getBgm() const { return bgm; }
    void setBgm(const string &bgm) { this->bgm = bgm; }

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
