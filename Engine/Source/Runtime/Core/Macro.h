#pragma once

#include "Core/PlatformDetection.h"
#include "Core/Log/LogSystem.h"
#include "Function/Global/GlobalContext.h"

//#include <chrono>
//#include <thread>

#define LOG_DEBUG(...) g_runtime_global_context.m_logger_system->GetLogger()->debug(__VA_ARGS__)

#define LOG_INFO(...) g_runtime_global_context.m_logger_system->GetLogger()->info(__VA_ARGS__)

#define LOG_WARN(...) g_runtime_global_context.m_logger_system->GetLogger()->warn(__VA_ARGS__)

#define LOG_ERROR(...) g_runtime_global_context.m_logger_system->GetLogger()->error(__VA_ARGS__)

#define LOG_FATAL(...) g_runtime_global_context.m_logger_system->GetLogger()->critical(__VA_ARGS__)

#ifdef NDEBUG
#define TAURUS_ASSERT(statement)
#else
#define TAURUS_ASSERT(statement) assert(statement)
#endif