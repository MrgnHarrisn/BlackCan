#include "input.h"

InputManager Input;

void InputManager::Update()
{
    m_previous_key_states = m_current_key_states;
}

void InputManager::SetKeyPressed(KeyCode key, bool isDown)
{
    m_current_key_states[key] = isDown;
}

bool InputManager::GetKey(KeyCode key) const
{
    auto it = m_current_key_states.find(key);

    if (it != m_current_key_states.end()) {
        return it->second;
    }

    return false;
}

bool InputManager::GetKeyDown(KeyCode key) const
{
    return GetKey(key);
}

bool InputManager::GetKeyUp(KeyCode key) const
{
    return !GetKey(key);
}

bool InputManager::GetKeyPressed(KeyCode key) const
{
    bool current = GetKey(key);
    
    bool previous = false;

    auto it = m_previous_key_states.find(key);
    if (it != m_previous_key_states.end()) {
        previous = current;
    }

    // if it is pressed now but wasn't before
    return current && !previous;
}

bool InputManager::GetKeyReleased(KeyCode key) const
{
    bool current = GetKey(key);

    bool previous = false;

    auto it = m_previous_key_states.find(key);
    if (it != m_previous_key_states.end()) {
        previous = current;
    }

    // not currently pressed but was last frame
    // therefore 'released'
    return !current && previous;
}