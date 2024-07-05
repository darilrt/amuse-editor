#include <core.hpp>
#include <imgui/imgui.h>

#include "editor/windows/components.hpp"
#include "icons.hpp"

void ComponentsEditor::on_init()
{
}

void ComponentsEditor::on_gui()
{
    auto style = ImGui::GetStyle();
    Vec2 size = ImGui::GetContentRegionAvail();
    Vec2 pos = ImGui::GetCursorPos();

    ImGui::Selectable(
        "##ComponentName",
        false,
        ImGuiSelectableFlags_AllowItemOverlap,
        ImVec2(size.x, icon_size + style.FramePadding.y * 2));

    ImGui::SetCursorPos(Vec2(pos.x + style.FramePadding.x, pos.y + style.FramePadding.y));
    ImGui::Image(ICON_CPP);
    ImGui::SameLine();
    ImGui::Text("ComponentName");
}