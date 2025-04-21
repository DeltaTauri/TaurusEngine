#include "GlobalContext.h"
#include "Core/Log/LogSystem.h"
#include "Core/Window/WindowSystem.h"
#include "Function/Render/RenderSystem.h"
#include "Function/Input/InputSystem.h"

namespace Taurus
{
    RuntimeGlobalContext g_runtime_global_context;

    void RuntimeGlobalContext::StartSystems()
    {
        m_logger_system = std::make_shared<LogSystem>();
        m_window_system = std::make_shared<WindowSystem>();
        m_input_system = std::make_shared<InputSystem>();
        m_render_system = std::make_shared<RenderSystem>();
    }

    void RuntimeGlobalContext::ShutdownSystems()
    {
        m_render_system.reset();
        m_input_system.reset();
        m_window_system.reset();
        m_logger_system.reset();
    }
}