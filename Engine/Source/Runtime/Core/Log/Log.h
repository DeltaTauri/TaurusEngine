#pragma once

#include <spdlog/spdlog.h>

namespace Taurus
{
    class Log final
    {
    public:
        static void Init();
        static std::shared_ptr<spdlog::logger>& GetLogger() { return m_logger; }

    private:
        static std::shared_ptr<spdlog::logger> m_logger;
    };
}

#define LOG_DEBUG(...) Taurus::Log::GetLogger()->debug(__VA_ARGS__)

#define LOG_INFO(...) Taurus::Log::GetLogger()->info(__VA_ARGS__)

#define LOG_WARN(...) Taurus::Log::GetLogger()->warn(__VA_ARGS__)

#define LOG_ERROR(...) Taurus::Log::GetLogger()->error(__VA_ARGS__)

#define LOG_FATAL(...) Taurus::Log::GetLogger()->critical(__VA_ARGS__)