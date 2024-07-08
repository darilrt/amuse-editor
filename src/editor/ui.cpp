#include "editor/ui.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "icons.hpp"

float ui::center = 0.35f;

static const ImGuiDataTypeInfo GDataTypeInfo[] =
    {
        {sizeof(char), "S8", "%d", "%d"}, // ImGuiDataType_S8
        {sizeof(unsigned char), "U8", "%u", "%u"},
        {sizeof(short), "S16", "%d", "%d"}, // ImGuiDataType_S16
        {sizeof(unsigned short), "U16", "%u", "%u"},
        {sizeof(int), "S32", "%d", "%d"}, // ImGuiDataType_S32
        {sizeof(unsigned int), "U32", "%u", "%u"},
#ifdef _MSC_VER
        {sizeof(ImS64), "S64", "%I64d", "%I64d"}, // ImGuiDataType_S64
        {sizeof(ImU64), "U64", "%I64u", "%I64u"},
#else
        {sizeof(ImS64), "S64", "%lld", "%lld"}, // ImGuiDataType_S64
        {sizeof(ImU64), "U64", "%llu", "%llu"},
#endif
        {sizeof(float), "float", "%.3f", "%f"},  // ImGuiDataType_Float (float are promoted to double in va_arg)
        {sizeof(double), "double", "%f", "%lf"}, // ImGuiDataType_Double
};

bool ui::InputVectorN(const char *label, ImGuiDataType data_type, void *p_data, int components, float v_speed, const void *p_min, const void *p_max, ImGuiSliderFlags flags)
{
    ImGuiWindow *window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext &g = *GImGui;
    bool value_changed = false;
    ImGui::BeginGroup();
    ImGui::PushID(label);
    ImGui::PushMultiItemsWidths(components, ImGui::CalcItemWidth());
    size_t type_size = GDataTypeInfo[data_type].Size;

    const char *formats[] = {"X: %0.2f", "Y: %0.2f", "Z: %0.2f", "W: %0.2f"};

    for (int i = 0; i < components; i++)
    {
        ImGui::PushID(i);
        if (i > 0)
            ImGui::SameLine(0, g.Style.ItemInnerSpacing.x);
        value_changed |= ImGui::DragScalar("", data_type, p_data, v_speed, p_min, p_max, formats[i], flags);
        ImGui::PopID();
        ImGui::PopItemWidth();
        p_data = (void *)((char *)p_data + type_size);
    }
    ImGui::PopID();

    const char *label_end = ImGui::FindRenderedTextEnd(label);
    if (label != label_end)
    {
        ImGui::SameLine(0, g.Style.ItemInnerSpacing.x);
        ImGui::TextEx(label, label_end);
    }

    ImGui::EndGroup();
    return value_changed;
}

bool ui::InputVector2(const char *label, float *v, float v_speed, float v_min, float v_max, ImGuiSliderFlags flags)
{
    return InputVectorN(label, ImGuiDataType_Float, v, 2, v_speed, &v_min, &v_max, flags);
}

bool ui::InputVector3(const char *label, float *v, float v_speed, float v_min, float v_max, ImGuiSliderFlags flags)
{
    return InputVectorN(label, ImGuiDataType_Float, v, 3, v_speed, &v_min, &v_max, flags);
}

bool ui::InputVector4(const char *label, float *v, float v_speed, float v_min, float v_max, ImGuiSliderFlags flags)
{
    return InputVectorN(label, ImGuiDataType_Float, v, 4, v_speed, &v_min, &v_max, flags);
}

bool ui::TreeNodeFileExplorer(void *icon, const ImVec2 &_icon_size, const ImVec2 &uv0, const ImVec2 &uv1, const char *label, bool leaf)
{
    ImGuiWindow *window = ImGui::GetCurrentWindow();

    ImGuiContext &g = *GImGui;
    const ImGuiStyle &style = g.Style;

    const ImGuiID id = window->GetID(label);

    ImVec2 padding = style.FramePadding;

    ImRect frame_bb;
    frame_bb.Min.x = window->WorkRect.Min.x;
    frame_bb.Min.y = window->DC.CursorPos.y;
    frame_bb.Max.x = window->WorkRect.Max.x;
    frame_bb.Max.y = window->DC.CursorPos.y + _icon_size.y + padding.y * 2;

    ImVec2 text_pos(window->DC.CursorPos.x + padding.x, window->DC.CursorPos.y + padding.y);

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(frame_bb, id, &hovered, &held, 0);

    const ImU32 bg_col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered
                                                                                                : ImGuiCol_Header);
    bool is_open = ImGui::TreeNodeUpdateNextOpen(id, 0);

    if (pressed)
    {
        ImGui::TreeNodeSetOpen(id, !is_open);
    }

    // Render

    if (hovered || held)
        ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, bg_col, true, 0);

    if (g.NavId == id)
        ImGui::RenderNavHighlight(frame_bb, id);

    if (!leaf)
    {
        window->DC.CursorPos = text_pos;

        if (is_open)
            ImGui::Image(ICON_ARROW_DOWN);
        else
            ImGui::Image(ICON_ARROW_RIGHT);

        text_pos.x += _icon_size.x + style.ItemSpacing.x;
    }

    window->DC.CursorPos = text_pos;
    ImGui::Image(icon, _icon_size, uv0, uv1);
    text_pos.x += _icon_size.x + style.ItemSpacing.x;

    ImGui::RenderText(text_pos, label, 0, true);

    window->DC.CursorPos.y = frame_bb.Max.y;

    window->DC.CursorPos = frame_bb.Min;
    ImGui::ItemSize(frame_bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(frame_bb, id))
        return false;

    if (is_open && !leaf)
    {
        ImGui::TreePush(label);
    }

    return is_open;
}
