#include "editor/windows/inspector.hpp"
#include "editor/editor.hpp"
#include "imgui/imgui.h"
#include "icons.hpp"

#include "inspectors/transform.hpp"

void draw_component_helpers(Actor *actor, Editor *editor, InspectorEditor *inspector)
{
    std::vector<Shared<Component>> to_remove;

    for (auto &component : actor->components)
    {
        ImGui::PushID(component.get());
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 0));
        ImGui::Checkbox("##", &component->enabled);
        ImGui::SameLine();

        bool open = ImGui::TreeNodeEx(component->_name.c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_AllowOverlap);
        ImGui::SameLine(ImGui::GetContentRegionMax().x - 20);
        if (ImGui::Button("×"))
        {
            editor->set_status(
                [component](Editor *editor)
                { ImGui::Text("Deleted component: %s", component->_name.c_str()); });

            to_remove.push_back(component);
            editor->set_edited();
        }
        ImGui::PopStyleVar();

        if (open)
        {
            auto custom_inspector = inspector->get_custom_inspector(component->_name);

            if (custom_inspector)
            {
                custom_inspector->on_inspector();
            }
            else
            {
                ImGui::Text("No inspector for %s", component->_name.c_str());
            }

            ImGui::TreePop();
        }
        ImGui::PopID();

        ImGui::Separator();
    }

    for (auto &component : to_remove)
    {
        actor->remove_component(component);
    }
}

void InspectorEditor::on_init()
{
    class DebugComponentInspector
    {
    public:
        static void on_inspector()
        {
            ImGui::Button("Debug inspector");
        };
    };

    register_custom_inspector<DebugComponentInspector>("DebugComponent");
    register_custom_inspector<TransformInspector>("Transform");
}

void InspectorEditor::on_gui()
{
    if (editor->selected_actor == nullptr)
        return;

    char buffer[256];
    strcpy_s(buffer, editor->selected_actor->name.c_str());

    float height = (ImGui::CalcTextSize("Name").y + ImGui::GetStyle().FramePadding.y * 2.0f) / 2.0f - icon_size / 2.0f;

    auto style = ImGui::GetStyle();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);
    ImGui::Image(ICON_OBJECT);
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - height);
    if (ImGui::InputText("Name", buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        editor->selected_actor->name = buffer;
        editor->set_edited();
    }
    ImGui::Separator();

    draw_component_helpers(editor->selected_actor.get(), editor, this);

    if (ImGui::Button("Add Component", ImVec2(-1, 0)))
    {
        ImGui::OpenPopup("Add Component");
    }

    if (ImGui::BeginPopup("Add Component"))
    {
        for (auto &pair : editor->engine->component_registry->factories)
        {
            if (pair.first == "MissingComponent")
                continue;

            if (ImGui::MenuItem(pair.first.c_str()))
            {
                auto component = pair.second();
                editor->selected_actor->add_component(component);
                editor->set_edited();
            }
        }

        ImGui::EndPopup();
    }
}