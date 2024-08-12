//
// Created by Brandon Friend on 8/7/24.
//



#ifndef CORE_H
#define CORE_H

#include <filesystem>

// =============================== [ PHYSICS ] =====================================
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Character/CharacterBase.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/PhysicsScene.h>
#include <Jolt/Physics/PhysicsSettings.h>

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






#define PH_EXPAND_MACRO(x) x
#define PH_STRINGIFY_MACRO(x) #x

#define PH_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define BIT(x) (1 << x)


namespace Phantom {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}



#include "Core/Log.h"
#include "Core/Assert.h"
#endif //CORE_H