#include <filesystem>
#include <string>
#include <toml.hpp>
#include <core.hpp>

#include "create_project.hpp"

const std::string __cmake_file(const std::string &name)
{
    std::ifstream file(std::filesystem::current_path() / "data" / "templates" / "cmake_components.txt");
    std::string source((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();

    size_t pos = 0;

    while ((pos = source.find("@name", pos)) != std::string::npos)
    {
        source.replace(pos, 5, name);
        pos += name.length();
    }

    return source;
}

const std::string __components_cpp(const std::string &name)
{
    std::ifstream file(std::filesystem::current_path() / "data" / "templates" / "components.cpp");
    std::string source((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();

    return source;
}

const std::string __components_hpp(const std::string &name)
{
    std::ifstream file(std::filesystem::current_path() / "data" / "templates" / "components.hpp");
    std::string source((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();

    return source;
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