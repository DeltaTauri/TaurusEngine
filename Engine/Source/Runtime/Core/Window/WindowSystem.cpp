#include "Core/Macro.h"
#include "Core/Window/WindowSystem.h"

namespace Taurus
{
    WindowSystem::WindowSystem()
    {
        WindowProps create_info;
        m_Window = Window::Create(create_info);
    }

    WindowSystem::~WindowSystem()
    {

    }

    void WindowSystem::Tick() const { m_Window->OnUpdate(); }

    bool WindowSystem::ShouldClose() const { return m_Window->ShouldClose(); }

    std::array<int, 2> WindowSystem::GetWindowSize() const { return std::array<int, 2>({ m_Window->GetWidth(), m_Window ->GetHeight()}); }

}
