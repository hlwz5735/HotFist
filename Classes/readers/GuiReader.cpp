//
// Created by 厉猛 on 2020/4/22.
//
#include "cocos2d.h"
#include "ui/UIButton.h"
#include "cocostudio/DictionaryHelper.h"
#include "GuiReader.h"
#include "JsonParser.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace hotfist;

static Node *createNodeFromDocument(rapidjson::Document jsonDoc);

Node *GuiReader::readDocument(std::string fileName) {
    return createNodeFromDocument(getDocumentFromResource(fileName));
}

static Node *createNodeFromDocument(rapidjson::Document jsonDoc) {
    const auto node = Node::create();
    const auto dicHelper = DictionaryHelper::getInstance();

    for (auto iterator = jsonDoc.MemberBegin(); iterator != jsonDoc.MemberEnd(); ++iterator) {
        const auto key = iterator->name.GetString();

        auto &value = iterator->value;
        const auto normalImage = dicHelper->getStringValue_json(value, "normalImage", "");
        const auto selectedImage = dicHelper->getStringValue_json(value, "selectedImage", normalImage);
        const auto disableImage = dicHelper->getStringValue_json(value, "disableImage", normalImage);
        const auto label = dicHelper->getStringValue_json(value, "label", "");
        const auto flippedX = dicHelper->getBooleanValue_json(value, "flippedX", false);
        const auto scale9 = dicHelper->getBooleanValue_json(value, "scale9", false);
        auto position = Point::ZERO;
        if (value.HasMember("position")) {
            position = Point(
                dicHelper->getFloatValue_json(value["position"], "x", 0),
                dicHelper->getFloatValue_json(value["position"], "y", 0)
            );
        }

        const auto button = ui::Button::create(normalImage, selectedImage, disableImage, ui::Button::TextureResType::PLIST);
        button->setTitleText(label);
        button->setScale9Enabled(scale9);
        button->setFlippedX(flippedX);
        button->setPosition(position);
        button->setName(key);

        node->addChild(button);
    }
    node->setPosition(Point::ZERO);
    return node;
}
