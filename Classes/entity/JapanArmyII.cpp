//
//  JapanArmyII.cpp
//  HelloCpp
//
//  Created by 田子桐 on 14-8-19.
//
//
#include "JapanArmyII.h"

USING_NS_AX;

bool JapanArmyII::init() {
    if (!JapanArmyI::init()) {
        return false;
    }
    hp = 120;
    return true;
}

void JapanArmyII::initSprite() {
    JapanArmyI::initSprite();
    m_sprite->setColor(Color3B(200, 0, 0));
}
