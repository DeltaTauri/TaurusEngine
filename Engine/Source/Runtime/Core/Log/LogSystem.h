#pragma once

#include <spdlog/spdlog.h>

namespace Taurus
{
    class LogSystem final
    {
    public:
        LogSystem();
        ~LogSystem();
        std::shared_ptr<spdlog::logger>& GetLogger() { return m_logger; }

    private:
        std::shared_ptr<spdlog::logger> m_logger;
    };
}

