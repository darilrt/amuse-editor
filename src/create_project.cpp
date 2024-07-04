#include <filesystem>
#include <string>
#include <toml.hpp>
#include <core.hpp>

#include "create_project.hpp"

const std::string __cmake_file(const std::string &name)
{
    return "cmake_minimum_required(VERSION 3.5)\n\n"
           "# C++ standard\n"
           "set(CMAKE_CXX_STANDARD 20)\n"
           "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n"
           "# Project name\n"
           "project(" +
           name + ")\n"
                  "set(project_name \"" +
           name + "\")\n\n"
                  "# Add definition for shared library\n"
                  "add_compile_definitions(AMUSE_CORE_EXPORT)\n\n"
                  "# Add source files\n"
                  "file(GLOB_RECURSE source_files assets/components/*.cpp)\n\n"
                  "# Add library\n"
                  "add_library(\n"
                  "    ${project_name} SHARED \n"
                  "    engine/components.cpp\n"
                  "    ${source_files})\n\n"
                  "# Include directories\n"
                  "target_include_directories(${project_name} PUBLIC \"assets/components\")\n"
                  "target_include_directories(${project_name} PUBLIC \"engine/core/include\")\n\n"
                  "# Link the library\n"
                  "target_link_directories(${project_name} PUBLIC ${CMAKE_SOURCE_DIR}/engine/core/lib)\n"
                  "target_link_libraries(${project_name} AmuseCore)\n";
}

const std::string __components_cpp(const std::string &name)
{
    return "#include \"components.hpp\"\n\n"
           "# Use REGISTER_COMPONENT macro to register components inside the COMPONENTS function\n"
           "COMPONENTS\n"
           "{\n"
           "//    REGISTER_COMPONENT(ComponentName);\n"
           "}\n";
}

const std::string __components_hpp(const std::string &name)
{
    return "#pragma once\n\n"
           "#include <dll.hpp>\n"
           "#include <core.hpp>\n\n"
           "#define REGISTER_COMPONENT(C) engine->component_registry->register_component<C>(#C)\n\n"
           "#define COMPONENTS void loader(Engine *engine)\n\n"
           "extern \"C\" AMUSE_API void loader(Engine *engine);\n";
}

void create_project(const std::filesystem::path &path, const std::string &name)
{
    std::filesystem::create_directory(path);
    std::filesystem::create_directory(path / "assets");
    std::filesystem::create_directory(path / "assets" / "components");
    std::filesystem::create_directory(path / "engine");

    std::ofstream file(path / "project.toml");
    file << "name = \"" << name << "\"\n";
    file.close();

    std::ofstream cmake(path / "CMakeLists.txt");
    cmake << __cmake_file(name);
    cmake.close();

    std::ofstream components(path / "engine" / "components.cpp");
    components << __components_cpp(name);
    components.close();

    std::ofstream components_h(path / "engine" / "components.hpp");
    components_h << __components_hpp(name);
    components_h.close();

    std::filesystem::copy(
        std::filesystem::current_path() / "data" / "core",
        path / "engine" / "core",
        std::filesystem::copy_options::recursive);

    logger.info("Project created: {}", path.string());
}