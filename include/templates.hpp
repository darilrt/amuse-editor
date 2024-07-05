#pragma once

#include <string>
#include <filesystem>
#include <vector>

class Template
{
public:
    std::string tmpl_src;

    Template(const std::filesystem::path &path);

    std::string get(std::vector<std::pair<std::string, std::string>> replacements);
};