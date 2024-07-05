cmake_minimum_required(VERSION 3.5)

# C++ standard 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
project(AmuseCore)
set(project_name "AmuseCore")

# Add definition for shared library
add_compile_definitions(AMUSE_CORE_EXPORT)

# Add static library
file(GLOB_RECURSE SOURCES 
    src/*.cpp
    src/core/*.cpp
    src/core/gfx/*.cpp
    src/core/components/*.cpp
    src/imgui/*.cpp
    src/imgui/backends/*.cpp)


add_library(${project_name} SHARED ${SOURCES})


# Add the include directory
target_include_directories(${project_name} PUBLIC include)

# Add the SDL2 library
option(SDL_STATIC ON)
option(SDL_SHARED OFF)
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

# Link the SDL2 library
target_link_libraries(${project_name} SDL2::SDL2main)
target_link_libraries(${project_name} SDL2::SDL2-static)