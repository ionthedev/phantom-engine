cmake_minimum_required(VERSION 3.29)
add_executable(PhantomWorks)
add_executable(PH::Editor ALIAS PhantomWorks)

target_sources(
        PhantomWorks
        PRIVATE
        "src/PhantomWorks.cpp"
)

target_include_directories(
        PhantomWorks
        PRIVATE
        "src"
)

set_target_properties(
        PhantomWorks
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED TRUE
)


# Link against PhantomEngine
target_link_libraries(
        PhantomWorks
        PUBLIC
        PhantomEngine)
