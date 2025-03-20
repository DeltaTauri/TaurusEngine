#pragma once

#include <array>
#include "BaseWindow.h"

namespace Taurus
{
    class WindowSystem
    {
    public:
        WindowSystem();
        ~WindowSystem();
        void               Tick() const;
        bool               ShouldClose() const;
        Window& GetWindow()  { return *m_Window; };
        std::array<int, 2> GetWindowSize() const;

        void registerOnKeyFunc(onKeyFunc func) { m_Window->m_onKeyFunc.push_back(func); }
        void registerOnMouseButtonFunc(onMouseButtonFunc func) { m_Window->m_onMouseButtonFunc.push_back(func); }
        void registerOnCursorPosFunc(onCursorPosFunc func) { m_Window->m_onCursorPosFunc.push_back(func); }
        void registerOnScrollFunc(onScrollFunc func) { m_Window->m_onScrollFunc.push_back(func); }
        void registerOnWindowSizeFunc(onWindowSizeFunc func) { m_Window->m_onWindowSizeFunc.push_back(func); }

    private:
        std::unique_ptr<Window> m_Window;
    };
}
