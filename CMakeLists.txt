cmake_minimum_required(VERSION 3.19)  # Adjust version as needed
project(PhantomEngine)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

option(PRODUCTION_BUILD "Make this a production build" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

SET(PKGCONFIG_INSTALL_PREFIX "lib${LIB_SUFFIX}/pkgconfig/" CACHE STRING "Base directory for pkgconfig files")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization


if(MSVC)
    add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif()

set(SDL_STATIC ON)

# Add subdirectories for PhantomEngine and FearTheCrow
add_subdirectory(phantom-engine)
add_subdirectory(Fear-the-Crow)
add_subdirectory(phantom-works)
#target_link_libraries(ProjectCrowsFeet PRIVATE PhantomEngine PhantomWorks FearTheCrow)