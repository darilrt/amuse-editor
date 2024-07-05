#include "editor/ui.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

float ui::center = 0.35f;

void label_text(const char *label, const float center)
{
    auto style = ImGui::GetStyle();

    ImVec2 available = ImGui::GetContentRegionAvail();
    float text_col_width = available.x * center;

    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 text_size = ImGui::CalcTextSize(label);

    ImGui::SetCursorScreenPos(ImVec2(pos.x + text_col_width - text_size.x - style.FramePadding.x, pos.y + style.FramePadding.y));
    ImGui::Text(label);
    ImGui::SetCursorScreenPos(ImVec2(pos.x + text_col_width + style.FramePadding.x, pos.y));
}

bool ui::InputVector3(const char *label, float *values, const char *format)
{

    bool changed = false;
    ImGui::PushID(label);

    label_text(label, center);

    float width = ImGui::GetContentRegionAvail().x;

    ImGui::PushItemWidth(width - ImGui::GetStyle().FramePadding.x);
    changed |= ImGui::DragFloat3("##x", &values[0], 0.01f, 0.0f, 0.0f, format);
    ImGui::PopItemWidth();

    ImGui::PopID();

    return changed;
}