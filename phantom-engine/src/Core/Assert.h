//
// Created by Brandon Friend on 8/10/24.
//

#ifndef ASSERT_H
#define ASSERT_H

#include "Core/Core.h"
#include "Core/Log.h"
#include <filesystem>

#ifdef PH_ENABLE_ASSERTS

    #define PH_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { PH##type##ERROR(msg, __VA_ARGS__); PH_DEBUGBREAK(); } }
    #define PH_INTERNAL_ASSERT_WITH_MSG(type, check, ...) PH_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
    #define PH_INTERNAL_ASSERT_NO_MSG(type, check) PH_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", PH_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

    #define PH_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define PH_INTERNAL_ASSERT_GET_MACRO(...) PH_EXPAND_MACRO( PH_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, PH_INTERNAL_ASSERT_WITH_MSG, PH_INTERNAL_ASSERT_NO_MSG) )

    // Currently accepts at least the condition and one additional parameter (the message) being optional
    #define PH_ASSERT(...) PH_EXPAND_MACRO( PH_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
    #define PH_CORE_ASSERT(...) PH_EXPAND_MACRO( PH_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
    #define PH_ASSERT(...)
    #define PH_CORE_ASSERT(...)
#endif

#endif //ASSERT_H
