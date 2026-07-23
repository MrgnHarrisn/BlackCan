#pragma once

#include "KeyCode.h"
#include <unordered_map>

class InputManager
{
public:
    void Update();
    void SetKeyPressed(KeyCode key, bool isDown);

    bool GetKey(KeyCode key) const;
    bool GetKeyDown(KeyCode key) const;
    bool GetKeyUp(KeyCode key) const;
    bool GetKeyPressed(KeyCode key) const;
    bool GetKeyReleased(KeyCode key) const;
private:
    std::unordered_map<KeyCode, bool> m_current_key_states;
    std::unordered_map<KeyCode, bool> m_previous_key_states;
};

extern InputManager Input;