#pragma once

#include "core/gfx/mesh.hpp"
#include "core/gfx/gl.hpp"

#include <vector>

class Mesh
{
public:
    gfx::VertexArray vao;
    gfx::Buffer vbo;
    gfx::Buffer tbo;
    uint32_t vertex_count;

    Mesh();

    Mesh(std::vector<float> vertices, std::vector<float> uv);

    void set(std::vector<float> vertices, std::vector<float> uv);

    void draw();
};