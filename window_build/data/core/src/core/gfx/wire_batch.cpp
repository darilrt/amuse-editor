#include "core/gfx/wire_batch.hpp"

WireBatch::WireBatch() : vao(), vbo(gfx::BufferType::Array)
{
    vao.bind();
    vbo.bind();

    vbo.set_data(nullptr, 0, gfx::BufferUsage::DynamicDraw);

    vao.set_attribute(0, vbo, 3, gfx::DataType::Float, 3 * sizeof(float), 0);
}

void WireBatch::add_line(float x1, float y1, float z1, float x2, float y2, float z2)
{
    vertices.push_back(x1);
    vertices.push_back(y1);
    vertices.push_back(z1);

    vertices.push_back(x2);
    vertices.push_back(y2);
    vertices.push_back(z2);
}

void WireBatch::draw()
{
    vao.bind();
    vbo.bind();

    vbo.set_data(vertices.data(), vertices.size() * sizeof(float), gfx::BufferUsage::DynamicDraw);

    gfx::draw(
        vertices.size() / 3,
        0, 0, 0,
        gfx::PrimitiveType::Lines);
}

void WireBatch::clear()
{
    vertices.clear();
}