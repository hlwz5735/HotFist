//
// Created by 厉猛 on 2024-03-01.
//

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager {
public:
    enum Keys {
        DPAD_DOWN = 0,
        DPAD_LEFT,
        DPAD_RIGHT,
        DPAD_UP,

        BTN_JUMP,
        BTN_ATTACK,

        KEYS_MAX
    };

    static InputManager *getInstance();
    static void destroyInstance();

    bool isKeyPressed(int keyCode) const;
    bool isKeyTriggered(int keyCode) const;
    bool isKeyReleased(int keyCode) const;
    void setKeyStatus(int keyCode, bool status);

    void update();
    void reset();
private:
    InputManager();
    ~InputManager();

    /// 前一帧的按键状态（用于持续性判断）
    bool *lastKeyStates;
    /// 当前按键状态（用于持续性判断）
    bool *keyStates;

    static InputManager *instance;
};

#endif //INPUTMANAGER_H
