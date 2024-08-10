#pragma once

#include "Core/Core.h"
#include "PhantomPch.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp">

#include <spdlog/spdlog.h>
#include "spdlog/fmt/ostr.h"
namespace Phantom {

	class Log
	{
	public:
		static void Init();

		static static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

// Core log macros
#define PH_CORE_TRACE(...)    ::Phantom::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PH_CORE_INFO(...)     ::Phantom::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PH_CORE_WARN(...)     ::Phantom::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PH_CORE_ERROR(...)    ::Phantom::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PH_CORE_CRITICAL(...) ::Phantom::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define PH_TRACE(...)         ::Phantom::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PH_INFO(...)          ::Phantom::Log::GetClientLogger()->info(__VA_ARGS__)
#define PH_WARN(...)          ::Phantom::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PH_ERROR(...)         ::Phantom::Log::GetClientLogger()->error(__VA_ARGS__)
#define PH_CRITICAL(...)      ::Phantom::Log::GetClientLogger()->critical(__VA_ARGS__)