#pragma once
#include "Function/Input/KeyCode.h"
#include <set>

namespace Taurus
{
    class InputSystem
    {
    public:
        InputSystem();
        ~InputSystem() = default;

        static bool IsKeyPressed(const KeyCode key);
    private:
        void OnKey(int key, int scancode, int action, int mods);
        static std::set<KeyCode> m_Keys;
    };
}