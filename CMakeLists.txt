cmake_minimum_required(VERSION 3.5)

# C++ standard 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
project(AmuseEditor)
set(project_name "AmuseEditor")

# Add the executable
file(GLOB_RECURSE SOURCES 
    src/*.cpp
    src/editor/*.cpp
    src/editor/windows/*.cpp)
    
add_executable(${project_name} ${SOURCES})

# Add the include directory
target_include_directories(${project_name} PUBLIC include)

# Add the library
add_subdirectory(core)

# Link the library
target_link_libraries(${project_name} AmuseCore)

# Copy shared libraries
add_custom_command(TARGET ${project_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:AmuseCore>
    $<TARGET_FILE_DIR:${project_name}>)

# Copy assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})