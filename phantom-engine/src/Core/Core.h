//
// Created by Brandon Friend on 8/7/24.
//



#ifndef CORE_H
#define CORE_H

#include <filesystem>
#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>

// Define export/import macros
#if defined(_WIN32) || defined(_WIN64)
    #ifdef PHANTOM_ENGINE_EXPORTS
        #define PHANTOM_API __declspec(dllexport)
    #else
        #define PHANTOM_API __declspec(dllimport)
    #endif
#else

    #include <signal.h>
    #define PHANTOM_API __attribute__((visibility("default")))
#endif



#endif //CORE_H


#define PH_EXPAND_MACRO(x) x
#define PH_STRINGIFY_MACRO(x) #x

#define PH_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define BIT(x) (1 << x)



#include "Core/Log.h"
#include "Core/Assert.h"