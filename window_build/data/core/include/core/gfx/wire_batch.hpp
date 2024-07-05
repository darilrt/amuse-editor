#pragma once

#include <vector>

#include "core/gfx/gl.hpp"

class WireBatch
{
public:
    std::vector<float> vertices;
    gfx::VertexArray vao;
    gfx::Buffer vbo;

    WireBatch();

    void add_line(float x1, float y1, float z1, float x2, float y2, float z2);

    void draw();

    void clear();
};