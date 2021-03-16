//
// Created by 厉猛 on 2020/4/28.
//

#ifndef HOTFISTREMASTER_SHOWIMGCOMMAND_H
#define HOTFISTREMASTER_SHOWIMGCOMMAND_H

#include "external/json/document.h"
#include "cocos/math/Vec2.h"
#include <string>

using std::string;
using cocos2d::Vec2;

/**
 * 显示图片的指令
 */
class ShowImgCommand
{
public:
    const string &getTextureName() const;

    void setTextureName(const string &textureName);

    const string &getTag() const;

    void setTag(const string &tag);

    const Vec2 &getPosition() const;

    void setPosition(const Vec2 &position);

    const Vec2 &getPivot() const;

    void setPivot(const Vec2 &pivot);

    int getOpacity() const;

    void setOpacity(int opacity);

    bool isFlippedX() const;

    void setFlippedX(bool flippedX);

    bool isFlippedY() const;

    void setFlippedY(bool flippedY);

    float getScaleX() const;

    void setScaleX(float scaleX);

    float getScaleY() const;

    void setScaleY(float scaleY);

    static ShowImgCommand fromJsonDocument(rapidjson::Value &object);

private:
    string textureName;
    string tag;
    Vec2 position;
    Vec2 pivot;
    int opacity;
    bool flippedX;
    bool flippedY;
    float scaleX;
    float scaleY;
};


#endif //HOTFISTREMASTER_SHOWIMGCOMMAND_H
