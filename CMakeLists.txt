cmake_minimum_required(VERSION 3.5)

# C++ standard 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
project(AmuseEditor)

# Add the executable
file(GLOB_RECURSE SOURCES 
    src/*.cpp
    src/editor/*.cpp
    src/editor/windows/*.cpp)
    
add_executable(AmuseEditor ${SOURCES})

# Add the include directory
target_include_directories(AmuseEditor PUBLIC include)

# Add the library
add_subdirectory(core)

# Link the library
target_link_libraries(AmuseEditor AmuseCore)

# Copy shared libraries
add_custom_command(TARGET AmuseEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_RUNTIME_DLLS:AmuseEditor>
    $<TARGET_FILE_DIR:AmuseEditor>)

# Copy data
add_custom_command(TARGET AmuseEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data
    ${CMAKE_BINARY_DIR}/data)

add_custom_command(TARGET AmuseEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/core 
    ${CMAKE_BINARY_DIR}/data/core)
    
add_custom_command(TARGET AmuseEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_BINARY_DIR}/data/core/lib)

add_custom_command(TARGET AmuseEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_LINKER_FILE:AmuseCore>
    ${CMAKE_BINARY_DIR}/data/core/lib/)