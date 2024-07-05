#include <cassert>

#include "core/graphic_manager.hpp"

void GraphicObject::render(const Mat4 &view, const Mat4 &projection)
{
    if (!mesh)
        return;

    // bind shader and set uniforms

    mesh->draw();
}

void GraphicManager::add(Shared<GraphicObject> object)
{
    objects.push_back(object);
}

void GraphicManager::render(const Mat4 &view, const Mat4 &projection, gfx::Framebuffer &framebuffer)
{
    framebuffer.bind();
    gfx::clear_color(1.0f, 0.0f, 0.0f, 1.0f);
    gfx::clear();

    for (auto &object : objects)
    {
        object->render(view, projection);
    }

    framebuffer.unbind();
}

void GraphicManager::present(const Texture &texture)
{
    gfx::unbind_framebuffer();
    gfx::clear();
}
