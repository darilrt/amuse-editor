#pragma once

#include <vector>

#include "editor/editor_window.hpp"
#include "visual_editor/visual_node.hpp"
#include "types.hpp"

#include "imgui/imgui.h"

class VisualComponentEditor : public EditorWindow
{
public:
    Vec2 position, canvas_start;
    std::vector<Shared<VisualNode>> nodes;
    std::vector<Shared<VisualConnection>> connections;

    void on_init() override;

    void on_gui() override;

    void begin_node(const char *title, Vec2 &pos, ImU32 color, int32_t elements);

    void end_node();
};