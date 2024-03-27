//
// Created by 厉猛 on 2024-03-01.
//

#ifndef STATUS_H
#define STATUS_H
#include <string>

namespace hotfist {

class Status {
public:
    virtual void onEnter() = 0;
    virtual void onExit() = 0;

    virtual void update(float dt) = 0;

    virtual const std::string& getName();
private:
    std::string name;
};

}

#endif //STATUS_H
