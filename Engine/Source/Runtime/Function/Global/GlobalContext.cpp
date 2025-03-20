#include "GlobalContext.h"
#include "Core/Log/LogSystem.h"
#include "Core/Window/WindowSystem.h"

namespace Taurus
{
    RuntimeGlobalContext g_runtime_global_context;

    void RuntimeGlobalContext::StartSystems()
    {
        m_logger_system = std::make_shared<LogSystem>();

        m_window_system = std::make_shared<WindowSystem>();
    }

    void RuntimeGlobalContext::ShutdownSystems()
    {
        m_logger_system.reset();
        
        m_window_system.reset();
    }
}