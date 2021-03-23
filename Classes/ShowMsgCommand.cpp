#include "cocostudio/DictionaryHelper.h"
using cocostudio::DictionaryHelper;
#include "ShowMsgCommand.h"

ShowMsgCommand ShowMsgCommand::fromJsonDocument(rapidjson::Value& object)
{
	const auto dictionaryHelper = DictionaryHelper::getInstance();

	auto cmd = ShowMsgCommand();

	cmd.text = dictionaryHelper->getStringValue_json(object, "text", "");
	cmd.avatar = dictionaryHelper->getStringValue_json(object, "avatar", "");
	cmd.position = dictionaryHelper->getStringValue_json(object, "position", "top");
	cmd.waitInput = dictionaryHelper->getBooleanValue_json(object, "waitInput", true);

	return cmd;
}
