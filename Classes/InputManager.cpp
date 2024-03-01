//
// Created by 厉猛 on 2024-03-01.
//

#include "PlatformMacros.h"
#include "InputManager.h"



InputManager *InputManager::getInstance() {
    if (!instance) {
        instance = new InputManager();
    }
    return instance;
}

void InputManager::destroyInstance() {
    AX_SAFE_DELETE(instance);
}

bool InputManager::isKeyPressed(int keyCode) const {
    return keyStates[keyCode];
}

bool InputManager::isKeyTriggered(int keyCode) const {
    return keyStates[keyCode] && !lastKeyStates[keyCode];
}

bool InputManager::isKeyReleased(int keyCode) const {
    return !keyStates[keyCode] && lastKeyStates[keyCode];
}

void InputManager::setKeyStatus(int keyCode, bool status) {
    if (keyCode < 0 || keyCode >= KEYS_MAX) {
        return;
    }
    keyStates[keyCode] = status;
}

void InputManager::update() {
    memcpy(lastKeyStates, keyStates, sizeof(bool) * KEYS_MAX);
}

void InputManager::reset() {
    memset(keyStates, 0, sizeof(bool) * KEYS_MAX);
    memset(lastKeyStates, 0, sizeof(bool) * KEYS_MAX);
}

InputManager::InputManager(): lastKeyStates(nullptr), keyStates(nullptr) {
    lastKeyStates = new bool[KEYS_MAX];
    keyStates = new bool[KEYS_MAX];
}

InputManager::~InputManager() {
    delete[] lastKeyStates;
    delete[] keyStates;

    lastKeyStates = nullptr;
    keyStates = nullptr;
}

InputManager *InputManager::instance = nullptr;
