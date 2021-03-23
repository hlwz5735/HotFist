#ifndef HOTFISTREMASTER_SHOWMSGCOMMAND_H
#define HOTFISTREMASTER_SHOWMSGCOMMAND_H

#include <string>
using std::string;
#include "cocos2d.h"
#include "external/json/document.h"

class ShowMsgCommand
{
public:
	static ShowMsgCommand fromJsonDocument(rapidjson::Value& object);
protected:
	CC_SYNTHESIZE_PASS_BY_REF(string, text, Text);
	CC_SYNTHESIZE_PASS_BY_REF(string, avatar, Avatar);
	CC_SYNTHESIZE_PASS_BY_REF(string, position, Position);

	bool waitInput;
public:
	virtual inline const bool& isWaitInput() const { return this->waitInput; }
	virtual inline void setWaitInput(const bool& val) { this->waitInput = val;  }
};

#endif
