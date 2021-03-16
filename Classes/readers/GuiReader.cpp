//
// Created by 厉猛 on 2020/4/22.
//
#include "cocos2d.h"
#include "cocos/ui/UIButton.h"
#include "cocostudio/DictionaryHelper.h"
#include "GuiReader.h"
#include "JsonParser.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace hotfist;

Node* createNodeFromDocument(rapidjson::Document jsonDoc);

Node* GuiReader::readDocument(std::string fileName)
{
    return createNodeFromDocument(getDocumentFromResource(fileName));
}

Node* createNodeFromDocument(rapidjson::Document jsonDoc) {
    auto dicHelper = DictionaryHelper::getInstance();

    auto node = Node::create();

    auto iterator = jsonDoc.MemberBegin();
    while (iterator != jsonDoc.MemberEnd())
    {
        auto key = iterator->name.GetString();

        auto normalImage = dicHelper->getStringValue_json(iterator->value, "normalImage", "");
        auto selectedImage = dicHelper->getStringValue_json(iterator->value, "selectedImage", normalImage);
        auto disableImage = dicHelper->getStringValue_json(iterator->value, "disableImage", normalImage);
        auto label = dicHelper->getStringValue_json(iterator->value, "label", "");
        auto flippedX = dicHelper->getBooleanValue_json(iterator->value, "flippedX", false);
        auto scale9 = dicHelper->getBooleanValue_json(iterator->value, "scale9", false);
        auto position = Point::ZERO;
        if (iterator->value.HasMember("position"))
        {
            position = Point(
                    dicHelper->getFloatValue_json(iterator->value["position"], "x", 0),
                    dicHelper->getFloatValue_json(iterator->value["position"], "y", 0)
            );
        }

        auto button = ui::Button::create(normalImage, selectedImage, disableImage, ui::Button::TextureResType::PLIST);
        button->setTitleText(label);
        button->setScale9Enabled(scale9);
        button->setFlippedX(flippedX);
        button->setPosition(position);
        button->setName(key);

        node->addChild(button);

        iterator++;
    }
    node->setPosition(Point::ZERO);
    return node;
}