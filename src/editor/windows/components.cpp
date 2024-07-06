#include <core.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "editor/windows/components.hpp"
#include "editor/editor.hpp"
#include "icons.hpp"

enum __gui_asset_flags : uint32_t
{
    None = 0,
    Leaf = 1,
    Open = 2,
};

bool __gui_asset(
    void *icon,
    const Vec2 &_icon_size,
    const Vec2 &uv0,
    const Vec2 &uv1,
    const char *name,
    uint32_t flags = __gui_asset_flags::None)
{
    auto style = ImGui::GetStyle();
    Vec2 size = ImGui::GetContentRegionAvail();
    Vec2 pos = ImGui::GetCursorPos();
    Vec2 text_size = ImGui::CalcTextSize(name);

    ImGuiID id = ImGui::GetID(name);
    ImGuiTreeNodeFlags _flags = ImGuiTreeNodeFlags_None;

    if (flags & __gui_asset_flags::Leaf)
    {
        _flags |= ImGuiTreeNodeFlags_Leaf;
    }

    bool is_open = ImGui::TreeNodeUpdateNextOpen(id, _flags);
    bool is_selected = false;

    if (!(flags & __gui_asset_flags::Leaf))
    {
        auto cursor = ImGui::GetCursorPos();
        ImGui::InvisibleButton("##Arrow", ImVec2(icon_size, icon_size + style.FramePadding.y * 2));

        if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
            ImGui::TreeNodeSetOpen(id, !is_open);
        }

        if (ImGui::IsItemHovered())
        {
            is_selected = true;
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        }

        ImGui::SetCursorPos(cursor);
    }

    ImGui::Selectable(
        "##",
        is_selected,
        ImGuiSelectableFlags_AllowItemOverlap,
        ImVec2(size.x, icon_size + style.FramePadding.y * 2));

    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
    {
        ImGui::TreeNodeSetOpen(id, !is_open);
    }

    ImGui::SetCursorPos(Vec2(pos.x + style.FramePadding.x, pos.y + style.FramePadding.y));

    if (flags & __gui_asset_flags::Leaf)
    {
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + icon_size + style.ItemSpacing.x);
    }
    else if (is_open)
    {
        ImGui::Image(ICON_ARROW_DOWN);
        ImGui::SameLine();
    }
    else
    {
        ImGui::Image(ICON_ARROW_RIGHT);
        ImGui::SameLine();
    }

    ImGui::Image(icon, _icon_size, uv0, uv1);
    ImGui::SameLine();
    ImGui::SetCursorPos(Vec2(
        ImGui::GetCursorPosX() + style.FramePadding.x,
        pos.y + style.FramePadding.y + (icon_size / 2.0f) - (text_size.y / 2.0f)));
    ImGui::Text(name);

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + style.FramePadding.y);

    return is_open;
}

void AssetsEditor::on_init()
{
}

void AssetsEditor::on_gui()
{
    auto style = ImGui::GetStyle();
    Vec2 size = ImGui::GetContentRegionAvail();
    Vec2 pos = ImGui::GetCursorPos();

    if (__gui_asset(ICON_FOLDER, "Actors"))
    {
        __gui_asset(ICON_OBJECT, "MainMenu", __gui_asset_flags::Leaf);
        __gui_asset(ICON_OBJECT, "Player", __gui_asset_flags::Leaf);
    }

    if (__gui_asset(ICON_FOLDER, "Components"))
    {
        __gui_asset(ICON_CPP, "TestComponent", __gui_asset_flags::Leaf);
        __gui_asset(ICON_CPP, "PlayerController", __gui_asset_flags::Leaf);
        __gui_asset(ICON_CPP, "CameraController", __gui_asset_flags::Leaf);
    }
}