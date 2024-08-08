# PhantomEngine/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(PhantomEngine)

# FetchContent configuration
include(FetchContent)

# Fetch Bullet3
FetchContent_Declare(
        bullet3
        GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
        GIT_TAG master
)
FetchContent_MakeAvailable(bullet3)

# Fetch EnTT
FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG master
)
FetchContent_MakeAvailable(entt)

# Fetch Raylib-cpp
FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG master
)
FetchContent_MakeAvailable(raylib_cpp)

# Fetch Raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# Include directories
include_directories(
        ${bullet3_SOURCE_DIR}/src
        ${entt_SOURCE_DIR}/src
        ${raylib_cpp_SOURCE_DIR}/include
        ${raylib_SOURCE_DIR}/src
        src/ThirdParty/rlImGui/
        src/ThirdParty/imgui-docking/imgui
)

add_subdirectory(src/ThirdParty/imgui-docking)
add_subdirectory(src/ThirdParty/rlImGui)

# Create PhantomEngine library
add_library(PhantomEngine
        src/Core/Core.h
        src/Core/Program.cpp
        src/Core/Program.h
        # Add other source files as necessary
)

add_executable(Phantom_Run src/main.cpp)

# Link dependencies
target_link_libraries(PhantomEngine
        PRIVATE
        Bullet3Common
        EnTT::EnTT
        raylib_cpp
        raylib
        rlimgui
        imgui
)
