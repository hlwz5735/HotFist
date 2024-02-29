#ifndef HOTFISTREMASTER_MOVEIMGCOMMAND_H
#define HOTFISTREMASTER_MOVEIMGCOMMAND_H

#include <string>
using std::string;
#include "cocos2d.h"
#include "external/json/document.h"
using cocos2d::Vec2;

class MoveImgCommand
{
public:
	static MoveImgCommand fromJsonDocument(rapidjson::Value& object);

protected:
	AX_SYNTHESIZE_PASS_BY_REF(string, tag, Tag);
	AX_SYNTHESIZE_PASS_BY_REF(int, duration, Duration);
	AX_SYNTHESIZE_PASS_BY_REF(int, opacity, Opacity);
	AX_SYNTHESIZE_PASS_BY_REF(Vec2, position, Position);

	AX_SYNTHESIZE_PASS_BY_REF(bool, flippedX, FlippedX);
	AX_SYNTHESIZE_PASS_BY_REF(bool, flippedY, FlippedY);
	AX_SYNTHESIZE_PASS_BY_REF(float, scaleX, ScaleX);
	AX_SYNTHESIZE_PASS_BY_REF(float, scaleY, ScaleY);
protected:
	bool moveAbsolute;
	bool visible;
public:
	virtual inline const bool& isMoveAbsolute() const { return moveAbsolute; }
	virtual inline void setMoveAbsolute(const bool& val) { this->moveAbsolute = val; }
	virtual inline const bool& isVisible() const { return visible; }
	virtual inline void setVisible(const bool& val) { this->visible = val; }
};

#endif
