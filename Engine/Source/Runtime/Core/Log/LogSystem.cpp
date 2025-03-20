#include "LogSystem.h"

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Taurus
{
    LogSystem::LogSystem()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);
        console_sink->set_pattern("[%T][%^%l%$] %v");

        const spdlog::sinks_init_list sink_list = {console_sink};
        m_logger = std::make_shared<spdlog::logger>("TAURUS", sink_list.begin(), sink_list.end());
        m_logger->set_level(spdlog::level::trace);
        m_logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(m_logger);
    }

    LogSystem::~LogSystem()
    {
        m_logger->flush();
        spdlog::drop_all();
    }
}