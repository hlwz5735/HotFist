#ifndef HOTFISTREMASTER_SHOWMSGCOMMAND_H
#define HOTFISTREMASTER_SHOWMSGCOMMAND_H

#include <string>
#include "cocos2d.h"
#include "external/json/document.h"
using std::string;

class ShowMsgCommand
{
public:
	static ShowMsgCommand fromJsonDocument(rapidjson::Value& object);

	bool isWaitInput() const { return this->waitInput; }
	void setWaitInput(const bool val) { this->waitInput = val;  }
protected:
	AX_SYNTHESIZE_PASS_BY_REF(string, text, Text);
	AX_SYNTHESIZE_PASS_BY_REF(string, avatar, Avatar);
	AX_SYNTHESIZE_PASS_BY_REF(string, position, Position);

	bool waitInput = true;
};

#endif
