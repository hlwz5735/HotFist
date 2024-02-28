//
// Created by 厉猛 on 2020/4/28.
//

#ifndef HOTFISTREMASTER_SHOWIMGCOMMAND_H
#define HOTFISTREMASTER_SHOWIMGCOMMAND_H

#include <string>
using std::string;
#include "cocos2d.h"
#include "external/json/document.h"
using cocos2d::Vec2;

/**
 * 显示图片的指令
 */
class ShowImgCommand
{
public:
    static ShowImgCommand fromJsonDocument(rapidjson::Value &object);

protected:
    AX_SYNTHESIZE_PASS_BY_REF(string, textureName, TextureName);
    AX_SYNTHESIZE_PASS_BY_REF(string, tag, Tag);
    AX_SYNTHESIZE_PASS_BY_REF(Vec2, position, Position);
    AX_SYNTHESIZE_PASS_BY_REF(Vec2, pivot, Pivot);
    AX_SYNTHESIZE_PASS_BY_REF(int, zIndex, ZIndex);
    AX_SYNTHESIZE_PASS_BY_REF(int, opacity, Opacity);

    AX_SYNTHESIZE_PASS_BY_REF(float, scaleX, ScaleX);
    AX_SYNTHESIZE_PASS_BY_REF(float, scaleY, ScaleY);
protected:
    bool flippedX;
    bool flippedY;
    bool visible;
public:
    virtual inline const bool& isFlippedX() const { return this->flippedX; }
    virtual inline void setFlippedX(const bool& val) { this->flippedX = val; }
    virtual inline const bool& isFlippedY() const { return this->flippedY; }
    virtual inline void setFlippedY(const bool& val) { this->flippedY = val; }
    virtual inline const bool& isVisible() const { return visible; }
    virtual inline void setVisible(const bool& val) { this->visible = val; }
};


#endif //HOTFISTREMASTER_SHOWIMGCOMMAND_H
