cmake_minimum_required(VERSION 3.19)
add_library(PhantomEngine SHARED
        src/Core/Log.cpp
        src/Core/Layer.cpp
        src/Core/Application.cpp
        src/Core/Application.h
        src/Core/Layer.h
        src/Core/LayerStack.cpp
        src/Core/LayerStack.h
        src/Core/Window.h
        src/Event_System/Event.h
        src/Event_System/ApplicationEvent.h
        src/Event_System/KeyEvent.h
        src/Event_System/MouseEvent.h
        src/Core/Assert.h
        src/Core/Window.cpp)
add_library(PH::Lib ALIAS PhantomEngine)



option(BUILD_SHARED_LIBS "Build shared libraries" ON)



target_sources(
        PhantomEngine
        PRIVATE
        "src/Core/Application.cpp"
)


#[[
# Add the PhantomEngine library
if(BUILD_SHARED_LIBS)
    add_library(PhantomEngine SHARED
            src/PhantomPch.h
            src/Core/EntryPoint.h
            src/Core/Application.h
            src/Core/Application.cpp
            src/Core/Log.h
            src/Core/Log.cpp
            # Add other source files as necessary
    )
    target_compile_definitions(PhantomEngine PUBLIC PHANTOM_ENGINE_EXPORTS)
else()
    add_library(PhantomEngine STATIC
            src/PhantomPch.h
            src/Core/EntryPoint.h
            src/Core/Application.h
            src/Core/Application.cpp
            src/Core/Log.h
            src/Core/Log.cpp
            # Add other source files as necessary
    )
endif()
]]

#-----------------------------------------------------------------------------------------------------

# FetchContent configuration
include(FetchContent)

# Fetch Bullet3
FetchContent_Declare(
        Jolt
        GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
        GIT_TAG master
        SOURCE_SUBDIR "Build"
)
FetchContent_MakeAvailable(Jolt)

# Fetch EnTT
FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG master
)
FetchContent_MakeAvailable(entt)


# Fetch Raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raylib-extras/raylib_multi_window_experimental.git
        GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.x
)
FetchContent_MakeAvailable(spdlog)

#-----------------------------------------------------------------------------------------------------


# Include directories
target_include_directories(PhantomEngine
        PUBLIC
        src
        ${jolt_SOURCE_DIR}/Build
        ${entt_SOURCE_DIR}/src
        ${raylib_SOURCE_DIR}/src
        ${spdlog_SOURCE_DIR}/src
        src/ThirdParty/rlImGui
        src/ThirdParty/imgui-docking/imgui
)

# Add third-party dependencies
add_subdirectory(src/ThirdParty/imgui-docking)
add_subdirectory(src/ThirdParty/rlImGui)

target_precompile_headers(
        PhantomEngine
        PUBLIC
        "src/PhantomPch.h"
)

set_target_properties(
        PhantomEngine
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED TRUE
)


# Link dependencies
target_link_libraries(PhantomEngine
        PUBLIC
        EnTT::EnTT
        raylib
        rlimgui
        imgui
        spdlog::spdlog
        Jolt
        #Jolt::Jolt




)

