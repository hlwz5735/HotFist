//
// Created by 厉猛 on 2020/4/28.
//

#include "cocostudio/DictionaryHelper.h"
using cocostudio::DictionaryHelper;
#include "ShowImgCommand.h"

ShowImgCommand ShowImgCommand::fromJsonDocument(rapidjson::Value &object)
{
    const auto dictionaryHelper = DictionaryHelper::getInstance();

    auto cmd = ShowImgCommand();

    cmd.textureName = dictionaryHelper->getStringValue_json(object, "textureName", "");
    cmd.tag = dictionaryHelper->getStringValue_json(object, "tag", "");

    if (object.HasMember("position"))
    {
        const auto x = dictionaryHelper->getFloatValue_json(object["position"], "x", 0);
        const auto y = dictionaryHelper->getFloatValue_json(object["position"], "y", 0);
        cmd.position = Vec2(x, y);
    }
    if (object.HasMember("pivot"))
    {
        const auto x = dictionaryHelper->getFloatValue_json(object["pivot"], "x", 0);
        const auto y = dictionaryHelper->getFloatValue_json(object["pivot"], "y", 0);
        cmd.pivot = Vec2(x, y);
    }

    cmd.opacity = dictionaryHelper->getIntValue_json(object, "opacity", 255);
    cmd.zIndex = dictionaryHelper->getIntValue_json(object, "zIndex", 0);
    cmd.flippedX = dictionaryHelper->getBooleanValue_json(object, "flippedX", false);
    cmd.flippedY = dictionaryHelper->getBooleanValue_json(object, "flippedY", false);
    cmd.scaleX = dictionaryHelper->getFloatValue_json(object, "scaleX", 1);
    cmd.scaleY = dictionaryHelper->getFloatValue_json(object, "scaleY", 1);
    cmd.visible = dictionaryHelper->getBooleanValue_json(object, "visible", true);

    return cmd;
}
