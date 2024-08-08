cmake_minimum_required(VERSION 3.14)
project(PhantomEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Fetch and build Raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(raylib)

# Fetch and build Raylib-cpp
FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(raylib_cpp)

# Fetch and build Bullet3
FetchContent_Declare(
        bullet3
        GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(bullet3)

# Fetch and build Entt
FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(entt)

# Add include directories for the engine
include_directories(
        include
        ${raylib_SOURCE_DIR}/src
        ${raylib_cpp_SOURCE_DIR}/include
        ${bullet3_SOURCE_DIR}/src
        ${entt_SOURCE_DIR}/src
)

# Add source files for the engine
set(SOURCES
        src/main.cpp
        # Add all your source files here
)

add_subdirectory(src/ThirdParty/imgui-docking)
add_subdirectory(src/ThirdParty/rlImGui)


# Create a library target for the engine
add_library(PhantomEngine STATIC ${SOURCES})

# Link the fetched libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        raylib
        raylib_cpp
        BulletDynamics
        BulletCollision
        LinearMath
        imgui
        rlimgui
        EnTT


)