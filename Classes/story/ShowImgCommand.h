//
// Created by 厉猛 on 2020/4/28.
//

#ifndef HOTFISTREMASTER_SHOWIMGCOMMAND_H
#define HOTFISTREMASTER_SHOWIMGCOMMAND_H

#include <string>
#include "cocos2d.h"
#include "external/json/document.h"
using std::string;
using cocos2d::Vec2;

/**
 * 显示图片的指令
 */
class ShowImgCommand
{
public:
    static ShowImgCommand fromJsonDocument(rapidjson::Value &object);

    bool isFlippedX() const { return this->flippedX; }
    void setFlippedX(const bool val) { this->flippedX = val; }
    bool isFlippedY() const { return this->flippedY; }
    void setFlippedY(const bool val) { this->flippedY = val; }
    bool isVisible() const { return visible; }
    void setVisible(const bool val) { this->visible = val; }
protected:
    AX_SYNTHESIZE_PASS_BY_REF(string, textureName, TextureName);
    AX_SYNTHESIZE_PASS_BY_REF(string, tag, Tag);
    AX_SYNTHESIZE_PASS_BY_REF(Vec2, position, Position);
    AX_SYNTHESIZE_PASS_BY_REF(Vec2, pivot, Pivot);
    AX_SYNTHESIZE(int, zIndex, ZIndex);
    AX_SYNTHESIZE(int, opacity, Opacity);
    AX_SYNTHESIZE(float, scaleX, ScaleX);
    AX_SYNTHESIZE(float, scaleY, ScaleY);

    bool flippedX = false;
    bool flippedY = false;
    bool visible = true;
};

#endif //HOTFISTREMASTER_SHOWIMGCOMMAND_H
