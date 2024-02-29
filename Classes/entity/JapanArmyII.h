//
//  JapanArmyII.h
//  HelloCpp
//
//  Created by 田子桐 on 14-8-19.
//
//

#ifndef HelloCpp_JapanArmyII_h
#define HelloCpp_JapanArmyII_h

#include "JapanArmyI.h"

USING_NS_CC;

class JapanArmyII : public JapanArmyI {
public:
    CREATE_FUNC(JapanArmyII);

    bool init() override;
    void initSprite() override;
};

#endif
