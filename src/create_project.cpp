#include <filesystem>
#include <string>
#include <toml.hpp>
#include <core.hpp>

#include "create_project.hpp"

void create_project(const std::filesystem::path &path, const std::string &name)
{
    std::filesystem::create_directory(path);
    std::filesystem::create_directory(path / "assets");
    std::filesystem::create_directory(path / "assets" / "components");
    std::filesystem::create_directory(path / "packages");

    toml::value table;
    table["name"] = name;

    std::ofstream file(path / "project.toml");
    file << toml::format(table);
    file.close();

    std::ofstream cmake(path / "CMakeLists.txt");
    cmake << "cmake_minimum_required(VERSION 3.5)\n\n";
    cmake << "set(CMAKE_CXX_STANDARD 20)\n";
    cmake << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n";
    cmake << "project(" << name << ")\n\n";
    cmake << "add_library(" << name << " SHARED packages/components.cpp)\n\n";
    cmake << "target_include_directories(" << name << " PRIVATE assets)\n\n";
    cmake << "add_subdirectory(packages/core)\n\n";
    cmake << "target_link_libraries(" << name << " AmuseCore)\n";
    cmake.close();

    std::ofstream components(path / "packages" / "components.cpp");
    components << "#include <core.hpp>\n\n";
    components.close();

    std::ofstream components_h(path / "packages" / "components.hpp");
    components_h.close();

    logger.info("Project created: {}", path.string());
}