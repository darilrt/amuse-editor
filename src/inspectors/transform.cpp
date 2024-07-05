#include <imgui/imgui.h>
#include <core.hpp>

#include "inspectors/transform.hpp"

void TransformInspector::on_inspector()
{
    Transform transform;

    ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
    ImGui::DragFloat3("Rotation", &transform._euler_angles.x, 0.1f);
    ImGui::DragFloat3("Scale", &transform.scale.x, 0.1f);
}