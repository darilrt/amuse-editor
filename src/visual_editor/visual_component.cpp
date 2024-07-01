#include "visual_editor/visual_component.hpp"
#include "editor/editor.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

void VisualComponentEditor::on_init()
{
}

void VisualComponentEditor::on_gui()
{
    ImGuiChildFlags flags = ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY;
    ImVec2 ssize = ImVec2(150, ImGui::GetContentRegionAvail().y - 20);
    ImGui::BeginChild("##visual_component", ssize, flags, ImGuiWindowFlags_None);

    ImGui::Text("Visual Component Editor");

    static float zoom = 1.0f;
    ImGui::DragFloat("Zoom", &zoom, 0.01f, 0.1f, 10.0f);

    ImGui::EndChild();
    ImGui::SameLine();

    ImGuiIO &io = ImGui::GetIO();
    ImGuiStyle style = ImGui::GetStyle();

    const Vec2 window_padding = style.WindowPadding;

    canvas_start = ImGui::GetCursorScreenPos();
    Vec2 start = ImGui::GetCursorScreenPos();
    Vec2 end = ImGui::GetContentRegionAvail();
    end += start;

    canvas_start = start;

    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    draw_list->AddRectFilled(start, end, IM_COL32(36, 36, 46, 255));
    draw_list->PushClipRect(start, end, true);

    constexpr ImU32 GRID_COLOR = IM_COL32(20, 20, 30, 100);

    float size = 32.0f * zoom;

    for (float x = fmodf(-position.x, size); x < io.DisplaySize.x; x += size)
    {
        draw_list->AddLine(
            Vec2(start.x + x, start.y),
            Vec2(start.x + x, end.y),
            GRID_COLOR);
    }

    for (float y = fmodf(-position.y, size); y < io.DisplaySize.y; y += size)
    {
        draw_list->AddLine(
            Vec2(start.x, start.y + y),
            Vec2(end.x, start.y + y),
            GRID_COLOR);
    }

    // Axis only debug purposes
    draw_list->AddLine(Vec2(start.x, start.y - position.y), Vec2(end.x, start.y - position.y), IM_COL32(255, 0, 0, 255), 3.0f);
    draw_list->AddLine(Vec2(start.x - position.x, start.y), Vec2(start.x - position.x, end.y), IM_COL32(0, 255, 0, 255), 3.0f);

    // handle dragging
    ImGui::PushID("canvas");

    ImVec2 button_size = end - start;

    if (button_size.x == 0.0f || button_size.y == 0.0f)
    {
        ImGui::PopID();
        return;
    }

    ImGui::SetCursorScreenPos(start);
    ImGui::InvisibleButton("canvas", button_size, ImGuiButtonFlags_MouseButtonMask_);

    const bool is_hovered = ImGui::IsItemHovered();
    const bool is_active = ImGui::IsItemActive();

    if (ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
    {
        position.x -= io.MouseDelta.x;
        position.y -= io.MouseDelta.y;
    }

    if (io.KeyCtrl && io.MouseWheel != 0.0f)
    {
        zoom += io.MouseWheel * 0.1f;
    }

    if (zoom < 0.1f)
        zoom = 0.1f;

    io.Fonts->Fonts[2]->Scale = zoom;
    ImGui::PushFont(io.Fonts->Fonts[2]);
    for (auto &node : nodes)
    {
        begin_node(node->title.c_str(), node->position, IM_COL32(50, 50, 200, 100), 3);
        // ImGui::Text("El que");
        // ImGui::Text("lea");
        // ImGui::Text("es gay");
        end_node();
    }
    ImGui::PopFont();

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::MenuItem("Add Node"))
        {
            auto node = Shared<VisualNode>(new VisualNode());
            node->title = "Node";
            node->position = ImVec2(0, 0);
            nodes.push_back(node);
        }

        ImGui::EndPopup();
    }

    ImGui::PopID();

    draw_list->PopClipRect();
}

void VisualComponentEditor::begin_node(const char *title, Vec2 &pos, ImU32 color, int32_t elements)
{
    ImGuiIO &io = ImGui::GetIO();

    float scale = io.Fonts->Fonts[2]->Scale;

    ImGuiStyle &style = ImGui::GetStyle();
    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    Vec2 local_pos = pos - position;
    Vec2 node_position = canvas_start + local_pos;

    ImVec2 title_size = ImGui::CalcTextSize(title);
    Vec2 frame_size = Vec2(
        title_size.x + style.FramePadding.x * 4 * scale,
        title_size.y + style.FramePadding.y * 2 * scale);

    draw_list->AddRectFilled(
        node_position,
        node_position + title_size,
        color,
        style.FrameRounding * 2.0f,
        ImDrawFlags_RoundCornersTop);

    draw_list->AddText(
        ImVec2(node_position.x + style.FramePadding.x * 2, node_position.y + style.FramePadding.y),
        IM_COL32(255, 255, 255, 255),
        title);

    // ImVec2 body_pos = ImVec2(node_position.x, node_position.y + frame_size.y);
    // ImVec2 body_size = ImVec2(frame_size.x, style.FramePadding.y * 2 + elements * ImGui::GetFontSize() + style.ItemSpacing.y * (elements - 1));

    // draw_list->AddRectFilled(body_pos, ImVec2(body_pos.x + body_size.x, body_pos.y + body_size.y), IM_COL32(50, 50, 50, 200), style.FrameRounding * 2.0f, ImDrawFlags_RoundCornersBottom);

    // ImGui::SetCursorScreenPos(node_position);
    // ImGui::PushID("##button_test");
    // ImGui::InvisibleButton(
    //     "##",
    //     ImVec2(frame_size.x, frame_size.y + body_size.y),
    //     ImGuiButtonFlags_MouseButtonMask_);

    // if (ImGui::IsItemHovered())
    // {
    //     draw_list->AddRect(
    //         node_position,
    //         ImVec2(
    //             node_position.x + frame_size.x,
    //             node_position.y + frame_size.y + body_size.y),
    //         IM_COL32(255, 255, 255, 50),
    //         style.FrameRounding * 2.0f,
    //         ImDrawFlags_RoundCornersAll,
    //         2.0f);
    // }

    // ImGui::PopID();

    // ImGui::SetCursorScreenPos(ImVec2(
    //     node_position.x + style.FramePadding.x * 2,
    //     node_position.y + style.FramePadding.y * 3 + title_size.y));
}

void VisualComponentEditor::end_node()
{
}