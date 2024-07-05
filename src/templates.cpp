#include <fstream>

#include "templates.hpp"

Template::Template(const std::filesystem::path &path)
{
    std::ifstream file(path);

    tmpl_src = std::string((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
}

std::string Template::get(std::vector<std::pair<std::string, std::string>> replacements)
{
    std::string src = tmpl_src;

    for (auto &replacement : replacements)
    {
        size_t pos = 0;

        while ((pos = src.find(replacement.first, pos)) != std::string::npos)
        {
            src.replace(pos, replacement.first.length(), replacement.second);
            pos += replacement.second.length();
        }
    }

    return src;
}
