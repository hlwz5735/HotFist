//
// Created by 厉猛 on 2024-02-29.
//

#include "MessageTip.h"

#include "Director.h"
#include "Global.h"

USING_NS_AX;

const static TTFConfig ttfConfig(
    "fonts/Deng.ttf",
    12 * SCALE_FACTOR,
    GlyphCollection::DYNAMIC,
    nullptr,
    true);

bool MessageTip::init() {
    if (!Node::init()) {
        return false;
    }

    auto label = Label::createWithTTF(ttfConfig, "轻触屏幕以继续");
    label->setScale(1 / SCALE_FACTOR);
    label->setAnchorPoint(Vec2(1, 1));
    text = label;
    this->addChild(text);

    return true;
}
