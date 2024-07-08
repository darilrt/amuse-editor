#pragma once

#include <imgui/imgui.h>

namespace ui
{
    extern float center;

    bool InputVectorN(const char *label, ImGuiDataType data_type, void *p_data, int components, float v_speed, const void *p_min, const void *p_max, ImGuiSliderFlags flags);

    bool InputVector2(const char *label, float *v, float v_speed, float v_min, float v_max, ImGuiSliderFlags flags);

    bool InputVector3(const char *label, float *v, float v_speed, float v_min, float v_max, ImGuiSliderFlags flags);

    bool InputVector4(const char *label, float *v, float v_speed, float v_min, float v_max, ImGuiSliderFlags flags);

    bool TreeNodeFileExplorer(void *icon, const ImVec2 &_icon_size, const ImVec2 &uv0, const ImVec2 &uv1, const char *label, bool leaf = false);
} // namespace ui