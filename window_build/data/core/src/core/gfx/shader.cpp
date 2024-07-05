#include <fstream>

#include "core/gfx/shader.hpp"

Shared<Shader> Shader::from_files(const char *vertex_path, const char *fragment_path)
{
    std::ifstream file(vertex_path, std::ios::in | std::ios::binary);
    std::string vertex_source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file = std::ifstream(fragment_path, std::ios::in | std::ios::binary);
    std::string fragment_source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    gfx::ShaderModule vertex_module(gfx::ShaderType::Vertex);
    vertex_module.set_source(vertex_source.c_str());
    vertex_module.compile();

    gfx::ShaderModule fragment_module(gfx::ShaderType::Fragment);
    fragment_module.set_source(fragment_source.c_str());
    fragment_module.compile();

    auto shader = new_shared<Shader>();

    shader->pipeline.attach_shader(vertex_module);
    shader->pipeline.attach_shader(fragment_module);
    shader->pipeline.link();

    return shader;
}