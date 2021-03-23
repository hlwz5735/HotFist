#include "cocostudio/DictionaryHelper.h"
using cocostudio::DictionaryHelper;
#include "MoveImgCommand.h"

#ifdef _MSC_VER
#undef GetObject
#endif

MoveImgCommand MoveImgCommand::fromJsonDocument(rapidjson::Value& object)
{
	const auto dictionaryHelper = DictionaryHelper::getInstance();

	auto cmd = MoveImgCommand();

	cmd.tag = dictionaryHelper->getStringValue_json(object, "tag", "");
	cmd.duration = dictionaryHelper->getIntValue_json(object, "duration", 1);
	cmd.opacity = dictionaryHelper->getIntValue_json(object, "opacity", 255);

	if (object.HasMember("position"))
	{
		const auto x = dictionaryHelper->getFloatValue_json(object["position"], "x", 0);
		const auto y = dictionaryHelper->getFloatValue_json(object["position"], "y", 0);
		cmd.position = Vec2(x, y);
	}

	cmd.moveAbsolute = dictionaryHelper->getBooleanValue_json(object, "moveAbsolute", false);
	cmd.flippedX = dictionaryHelper->getBooleanValue_json(object, "flippedX", false);
	cmd.flippedY = dictionaryHelper->getBooleanValue_json(object, "flippedY", false);
	cmd.scaleX = dictionaryHelper->getFloatValue_json(object, "scaleX", 1);
	cmd.scaleY = dictionaryHelper->getFloatValue_json(object, "scaleY", 1);
	cmd.visible = dictionaryHelper->getBooleanValue_json(object, "visible", true);

	return cmd;
}
