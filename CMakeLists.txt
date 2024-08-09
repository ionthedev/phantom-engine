# PhantomEngine/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(PhantomEngine)

set(CMAKE_CXX_STANDARD 17)


option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Add the PhantomEngine library
if(BUILD_SHARED_LIBS)
    add_library(PhantomEngine SHARED
            src/PhantomEngine.h
            src/Core/EntryPoint.h
            src/Core/Application.h
            src/Core/Application.cpp
            src/Core/Log.h
            src/Core/Log.cpp
            # Add other source files as necessary
    )
    target_compile_definitions(PhantomEngine PRIVATE PHANTOM_ENGINE_EXPORTS)
else()
    add_library(PhantomEngine STATIC
            src/PhantomEngine.h
            src/Core/EntryPoint.h
            src/Core/Application.h
            src/Core/Application.cpp
            src/Core/Log.h
            src/Core/Log.cpp
            # Add other source files as necessary
    )
endif()



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

FetchContent_Declare(
        spdlog
        https://github.com/gabime/spdlog.git
        GIT_TAG v1.x
)
FetchContent_MakeAvailable(spdlog)

# Include directories
target_include_directories(PhantomEngine
        PUBLIC
        ${bullet3_SOURCE_DIR}/src
        ${entt_SOURCE_DIR}/src
        ${raylib_cpp_SOURCE_DIR}/include
        ${raylib_SOURCE_DIR}/src
        ${spdlog_SOURCE_DIR}/src
        src/ThirdParty/rlImGui
        src/ThirdParty/imgui-docking/imgui
)

# Add third-party dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/src/ThirdParty/imgui-docking)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/ThirdParty/rlImGui)


# Link dependencies
target_link_libraries(PhantomEngine
        PUBLIC
        Bullet3Common
        EnTT::EnTT
        raylib
        raylib_cpp
        rlimgui
        imgui
        spdlog
)



# Install headers and library
install(TARGETS PhantomEngine DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/PhantomEngine FILES_MATCHING PATTERN "*.h")

# Create executable for testing