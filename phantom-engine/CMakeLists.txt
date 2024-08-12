cmake_minimum_required(VERSION 3.19)



file(GLOB_RECURSE RENDERER_SOURCES CONFIGURE_DEPENDS "src/Renderer/*.cpp")
file(GLOB_RECURSE RENDERER_HEADERS CONFIGURE_DEPENDS "src/Renderer/*.h")

add_library(PhantomEngine SHARED
        src/Core/Core.h
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
        src/Core/WindowBase.cpp
        src/Core/WindowBase.h
        ${RENDERER_SOURCES}
        ${RENDERER_HEADERS}
        src/Core/Window.cpp)
add_library(PH::Lib ALIAS PhantomEngine)

target_sources(
        PhantomEngine
        PRIVATE
        "src/Core/Application.cpp"
)

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
        ${raylib_cpp_SOURCE_DIR}/include
        ${raylib_SOURCE_DIR}/src
        ${spdlog_SOURCE_DIR}/src
        src/ThirdParty/rlImGui
        src/ThirdParty/imgui-docking/imgui
)

# Add third-party dependencies
add_subdirectory(src/ThirdParty/SDL-release-2.30.5)
add_subdirectory(src/ThirdParty/glad)
add_subdirectory(src/ThirdParty/stb_image)
add_subdirectory(src/ThirdParty/stb_truetype)
add_subdirectory(src/ThirdParty/glm)
add_subdirectory(src/ThirdParty/imgui-docking)
add_subdirectory(src/ThirdParty/gl2d)


set_property(TARGET PhantomEngine PROPERTY CXX_STANDARD 17)


target_compile_definitions(PhantomEngine PUBLIC GLFW_INCLUDE_NONE=1)

if(PRODUCTION_BUILD)
    # setup the ASSETS_PATH macro to be in the root folder of your exe
    target_compile_definitions(PhantomEngine PUBLIC RESOURCES_PATH="./resources/")

    target_compile_definitions(PhantomEngine PUBLIC PRODUCTION_BUILD=1)

else()
    # This is useful to get an ASSETS_PATH in your IDE during development
    target_compile_definitions(PhantomEngine PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions(PhantomEngine PUBLIC PRODUCTION_BUILD=0)

endif()



if(MSVC) # If using the VS compiler...

    target_compile_definitions(PhantomEngine PUBLIC _CRT_SECURE_NO_WARNINGS)

    #add this line if you want to remove the console!
    #set_target_properties(PhantomEngine PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console

    #set_property(TARGET PhantomEngine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
    #set_property(TARGET PhantomEngine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

endif()

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
        imgui
        spdlog::spdlog
        Jolt
        SDL2-static
        stb_image
        stb_truetype
        glad
        glm
        gl2d




)

