#pragma once

#include "editor/editor_window.hpp"
#include "core/gfx.hpp"

class SceneEditor : public EditorWindow
{
public:
    Unique<gfx::Image> color;
    Unique<gfx::Framebuffer> framebuffer;

    void on_init() override;

    void on_gui() override;

    void on_push_style() override;

    void on_pop_style() override;
};
