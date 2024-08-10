cmake_minimum_required(VERSION 3.19)  # Adjust version as needed
project(PhantomEngine)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Add subdirectories for PhantomEngine and FearTheCrow
add_subdirectory(phantom-engine)
add_subdirectory(Fear-the-Crow)
add_subdirectory(phantom-works)
#target_link_libraries(ProjectCrowsFeet PRIVATE PhantomEngine PhantomWorks FearTheCrow)