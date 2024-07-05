#include "core/gfx/mesh.hpp"

Mesh::Mesh() : vao(), vbo(gfx::BufferType::Array), tbo(gfx::BufferType::Array)
{
    vertex_count = 0;
}

Mesh::Mesh(std::vector<float> vertices, std::vector<float> uv) : vao(), vbo(gfx::BufferType::Array), tbo(gfx::BufferType::Array)
{
    set(vertices, uv);
}

void Mesh::set(std::vector<float> vertices, std::vector<float> uv)
{
    vertex_count = (uint32_t)(vertices.size() / 3);

    vbo.set_data(vertices.data(), vertices.size() * sizeof(float), gfx::BufferUsage::StaticDraw);
    tbo.set_data(uv.data(), uv.size() * sizeof(float), gfx::BufferUsage::StaticDraw);
    vao.set_attribute(0, vbo, 3, gfx::DataType::Float, 0, 0);
    vao.set_attribute(1, tbo, 2, gfx::DataType::Float, 0, 0);
}

void Mesh::draw()
{
    vao.bind();
    gfx::draw(vertex_count);
}
