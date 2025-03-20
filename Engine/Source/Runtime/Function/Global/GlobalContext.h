#pragma once

#include <memory>

namespace Taurus
{
    class LogSystem;
	class WindowSystem;
 
    class RuntimeGlobalContext
    {
    public:
        void StartSystems();
        void ShutdownSystems();

    public:
        std::shared_ptr<LogSystem>         m_logger_system;
        std::shared_ptr<WindowSystem>      m_window_system;
      
    };

    extern RuntimeGlobalContext g_runtime_global_context;
}