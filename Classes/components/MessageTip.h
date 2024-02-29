//
// Created by 厉猛 on 2024-02-29.
//

#ifndef MESSAGETIP_HPP
#define MESSAGETIP_HPP

#include "2d/Label.h"
#include "2d/Node.h"

class MessageTip: public ax::Node {
public:
    CREATE_FUNC(MessageTip);

    bool init() override;
    // void update(float dt) override;

private:
    ax::Label *text;
};


#endif //MESSAGETIP_HPP
