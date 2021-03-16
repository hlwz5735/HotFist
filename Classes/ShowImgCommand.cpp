//
// Created by 厉猛 on 2020/4/28.
//

#include "ShowImgCommand.h"
#include "cocostudio/DictionaryHelper.h"

using cocostudio::DictionaryHelper;

const string &ShowImgCommand::getTextureName() const
{
    return textureName;
}

void ShowImgCommand::setTextureName(const string &textureName)
{
    ShowImgCommand::textureName = textureName;
}

const string &ShowImgCommand::getTag() const
{
    return tag;
}

void ShowImgCommand::setTag(const string &tag)
{
    ShowImgCommand::tag = tag;
}

const Vec2 &ShowImgCommand::getPosition() const
{
    return position;
}

void ShowImgCommand::setPosition(const Vec2 &position)
{
    ShowImgCommand::position = position;
}

const Vec2 &ShowImgCommand::getPivot() const
{
    return pivot;
}

void ShowImgCommand::setPivot(const Vec2 &pivot)
{
    ShowImgCommand::pivot = pivot;
}

int ShowImgCommand::getOpacity() const
{
    return opacity;
}

void ShowImgCommand::setOpacity(int opacity)
{
    ShowImgCommand::opacity = opacity;
}

bool ShowImgCommand::isFlippedX() const
{
    return flippedX;
}

void ShowImgCommand::setFlippedX(bool flippedX)
{
    ShowImgCommand::flippedX = flippedX;
}

bool ShowImgCommand::isFlippedY() const
{
    return flippedY;
}

void ShowImgCommand::setFlippedY(bool flippedY)
{
    ShowImgCommand::flippedY = flippedY;
}

float ShowImgCommand::getScaleX() const
{
    return scaleX;
}

void ShowImgCommand::setScaleX(float scaleX)
{
    ShowImgCommand::scaleX = scaleX;
}

float ShowImgCommand::getScaleY() const
{
    return scaleY;
}

void ShowImgCommand::setScaleY(float scaleY)
{
    ShowImgCommand::scaleY = scaleY;
}

ShowImgCommand ShowImgCommand::fromJsonDocument(rapidjson::Value &object)
{
    const auto dictionaryHelper = DictionaryHelper::getInstance();

    auto cmd = ShowImgCommand();

    cmd.textureName = dictionaryHelper->getStringValue_json(object, "textureName", "");
    cmd.tag = dictionaryHelper->getStringValue_json(object, "tag", "");
//    cmd.textureName = object["textureName"].GetString();
//    cmd.tag = object["tag"].GetString();

    const auto positionObj = object["position"].GetObject();
    cmd.position = Vec2(dictionaryHelper->getFloatValue_json(positionObj, "x", 0),
            dictionaryHelper->getFloatValue_json(positionObj, "y", 0));

    const auto pivotObj = object["pivot"].GetObject();
    cmd.pivot = Vec2(dictionaryHelper->getFloatValue_json(pivotObj, "x", 0),
            dictionaryHelper->getFloatValue_json(pivotObj, "y", 0));

    cmd.opacity = dictionaryHelper->getIntValue_json(object, "opacity", 255);
    cmd.flippedX = dictionaryHelper->getBooleanValue_json(object, "flippedX", false);
    cmd.flippedY = dictionaryHelper->getBooleanValue_json(object, "flippedY", false);
    cmd.scaleX = dictionaryHelper->getFloatValue_json(object, "scaleX", 1);
    cmd.scaleY = dictionaryHelper->getFloatValue_json(object, "scaleY", 1);
    return cmd;
}
