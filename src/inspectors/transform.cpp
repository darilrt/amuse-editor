#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <core.hpp>

#include "inspectors/transform.hpp"
#include "editor/ui.hpp"

void TransformInspector::on_inspector(Component *component)
{
    Transform *transform = (Transform *)component;

    ui::InputVector3("Position", &transform->position.x, 0.1f, 0, 0, ImGuiSliderFlags_None);
    ui::InputVector3("Rotation", &transform->_euler_angles.x, 0.1f, 0, 0, ImGuiSliderFlags_None);
    ui::InputVector3("Scale", &transform->scale.x, 0.1f, 0, 0, ImGuiSliderFlags_None);
}