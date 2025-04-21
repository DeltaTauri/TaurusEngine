#pragma once

#include <memory>

namespace Taurus
{
    class LogSystem;
    class WindowSystem;
    class InputSystem;
    class RenderSystem;
 
    class RuntimeGlobalContext
    {
    public:
        void StartSystems();
        void ShutdownSystems();

    public:
        std::shared_ptr<LogSystem>         m_logger_system;
        std::shared_ptr<WindowSystem>      m_window_system;
        std::shared_ptr<InputSystem>       m_input_system;
        std::shared_ptr<RenderSystem>      m_render_system;
    };

    extern RuntimeGlobalContext g_runtime_global_context;
}