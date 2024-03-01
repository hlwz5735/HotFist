//
// Created by 厉猛 on 2024-03-01.
//

#ifndef STATUS_H
#define STATUS_H

namespace hotfist {

class Status {
public:
    virtual void onEnter() = 0;
    virtual void onExit() = 0;

    virtual void update(float dt) = 0;
private:
};

}

#endif //STATUS_H
