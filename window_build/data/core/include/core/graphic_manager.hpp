#pragma once

#include <vector>
#include <array>

#include "core/math.hpp"
#include "core/gfx.hpp"
#include "types.hpp"
#include "dll.hpp"

#define LAYER(x) (1 << x)

class GraphicObject
{
public:
    Shared<Mesh> mesh;

    AMUSE_API void render(const Mat4 &view, const Mat4 &projection);
};

class GraphicManager
{
public:
    std::vector<Shared<GraphicObject>> objects;

    AMUSE_API void add(Shared<GraphicObject> object);

    AMUSE_API void render(const Mat4 &view, const Mat4 &projection, gfx::Framebuffer &framebuffer);

    AMUSE_API void present(const Texture &texture);
};