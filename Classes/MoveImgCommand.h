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
	CC_SYNTHESIZE_PASS_BY_REF(string, tag, Tag);
	CC_SYNTHESIZE_PASS_BY_REF(int, duration, Duration);
	CC_SYNTHESIZE_PASS_BY_REF(int, opacity, Opacity);
	CC_SYNTHESIZE_PASS_BY_REF(Vec2, position, Position);

	CC_SYNTHESIZE_PASS_BY_REF(bool, flippedX, FlippedX);
	CC_SYNTHESIZE_PASS_BY_REF(bool, flippedY, FlippedY);
	CC_SYNTHESIZE_PASS_BY_REF(float, scaleX, ScaleX);
	CC_SYNTHESIZE_PASS_BY_REF(float, scaleY, ScaleY);
protected:
	bool moveAbsolute;
public:
	virtual inline const bool& isMoveAbsolute() const { return moveAbsolute; }
	virtual inline void setMoveAbsolute(const bool& val) { this->moveAbsolute = val; }
};

#endif
