//
// Created by Brandon Friend on 8/9/24.
//

#ifndef LOG_H
#define LOG_H
#include <memory>

#include "../PhantomPch.h"
#include "spdlog/spdlog.h"

namespace Phantom {
    class Log {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

//Core Log Macros
#define PH_CORE_TRACE(...) ::Phantom::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PH_CORE_INFO(...)  ::Phantom::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PH_CORE_WARN(...)  ::Phantom::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PH_CORE_ERROR(...) ::Phantom::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PH_CORE_FATAL(...) ::Phantom::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Core Log Macros
#define PH_TRACE(...)      ::Phantom::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PH_INFO(...)       ::Phantom::Log::GetClientLogger()->info(__VA_ARGS__)
#define PH_WARN(...)       ::Phantom::Log::GetClientLogger()->warm(__VA_ARGS__)
#define PH_ERROR(...)      ::Phantom::Log::GetClientLogger()->error(__VA_ARGS__)
#define PH_FATAL(...)      ::Phantom::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif //LOG_H
