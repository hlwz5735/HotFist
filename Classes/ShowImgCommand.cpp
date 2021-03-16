//
// Created by 厉猛 on 2020/4/28.
//

#include "cocostudio/DictionaryHelper.h"
using cocostudio::DictionaryHelper;
#include "ShowImgCommand.h"

#ifdef _MSC_VER
#undef GetObject
#endif

ShowImgCommand ShowImgCommand::fromJsonDocument(rapidjson::Value &object)
{
    const auto dictionaryHelper = DictionaryHelper::getInstance();

    auto cmd = ShowImgCommand();

    cmd.textureName = dictionaryHelper->getStringValue_json(object, "textureName", "");
    cmd.tag = dictionaryHelper->getStringValue_json(object, "tag", "");

    if (object.HasMember("position"))
    {
        auto positionObj = object["position"].GetObject();
        cmd.position = Vec2(dictionaryHelper->getFloatValue_json(positionObj, "x", 0),
            dictionaryHelper->getFloatValue_json(positionObj, "y", 0));
    }
    if (object.HasMember("pivot"))
    {
        auto pivotObj = object["pivot"].GetObject();
        cmd.pivot = Vec2(dictionaryHelper->getFloatValue_json(pivotObj, "x", 0),
            dictionaryHelper->getFloatValue_json(pivotObj, "y", 0));
    }

    cmd.opacity = dictionaryHelper->getIntValue_json(object, "opacity", 255);
    cmd.flippedX = dictionaryHelper->getBooleanValue_json(object, "flippedX", false);
    cmd.flippedY = dictionaryHelper->getBooleanValue_json(object, "flippedY", false);
    cmd.scaleX = dictionaryHelper->getFloatValue_json(object, "scaleX", 1);
    cmd.scaleY = dictionaryHelper->getFloatValue_json(object, "scaleY", 1);
    return cmd;
}
