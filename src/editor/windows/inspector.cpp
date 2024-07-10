#include <logger.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "editor/windows/inspector.hpp"
#include "editor/editor.hpp"
#include "imgui/misc/cpp/imgui_stdlib.h"
#include "icons.hpp"

#include "inspectors/transform.hpp"

bool __TreeNodeComponent(const char *label, bool *enabled, bool *remove)
{
    ImGuiWindow *window = ImGui::GetCurrentWindow();
    ImGuiContext &g = *GImGui;
    ImGuiID id = window->GetID(label);

    ImRect frame_bb(window->DC.CursorPos, ImVec2(0.0, 0.0));
    frame_bb.Max.x = window->WorkRect.Max.x;
    frame_bb.Max.y = window->DC.CursorPos.y + g.FontSize + g.Style.FramePadding.y * 2;

    ImVec2 text_pos(window->DC.CursorPos.x + g.Style.ItemSpacing.x, window->DC.CursorPos.y + g.Style.FramePadding.y);

    bool is_open = ImGui::TreeNodeUpdateNextOpen(id, 0);

    window->DC.CursorPos = text_pos;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::Checkbox("##", enabled);
    ImGui::PopStyleVar();
    ImGui::SameLine();

    if (is_open)
        ImGui::Image(ICON_ARROW_DOWN);
    else
        ImGui::Image(ICON_ARROW_RIGHT);

    ImGui::SameLine();

    text_pos.x = window->DC.CursorPos.x;

    window->DC.CursorPos.x = frame_bb.Max.x - icon_size - g.Style.FramePadding.x;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    if (ImGui::ImageButton(ICON_CROSS_V2))
    {
        *remove = true;
    }
    ImGui::PopStyleVar();

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(frame_bb, id, &hovered, &held, 0);

    const ImU32 bg_col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered
                                                                                                : ImGuiCol_Header);
    if (hovered)
        ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, bg_col, true, 0.0f);

    ImGui::RenderTextEllipsis(
        window->DrawList,
        text_pos,
        window->ClipRect.Max,
        window->ClipRect.Max.x,
        window->ClipRect.Max.x,
        label, nullptr, nullptr);

    if (pressed && hovered)
    {
        ImGui::TreeNodeSetOpen(id, !is_open);
    }

    window->DC.CursorPos = frame_bb.Min;
    ImGui::ItemSize(frame_bb, 0);
    if (!ImGui::ItemAdd(frame_bb, id))
        return false;

    if (is_open)
        ImGui::TreePush(label);

    return is_open;
}

void draw_component_helpers(Actor *actor, Editor *editor, InspectorEditor *inspector)
{
    std::vector<Shared<Component>> to_remove;

    for (auto &component : actor->components)
    {
        ImGui::PushID(component.get());

        bool remove = false;
        bool open = __TreeNodeComponent((component->_name + "##COMPONENT").c_str(), &component->enabled, &remove);

        if (remove)
        {
            editor->set_status(
                [component](Editor *editor)
                { ImGui::Text("Deleted component: %s", component->_name.c_str()); });

            to_remove.push_back(component);
            editor->set_edited();
        }

        if (open)
        {
            auto custom_inspector = inspector->get_custom_inspector(component->_name);

            if (custom_inspector != nullptr)
            {
                custom_inspector->on_inspector(component.get());
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
        static void on_inspector(Component *component)
        {
            ImGui::Text("Debug component inspector");
        };
    };

    register_custom_inspector<DebugComponentInspector>("DebugComponent");
    register_custom_inspector<TransformInspector>("Transform");
}

void InspectorEditor::on_gui()
{
    if (editor->selected_actor == nullptr)
        return;

    std::string buffer;
    buffer = editor->selected_actor->name;

    float height = (ImGui::CalcTextSize("Name").y + ImGui::GetStyle().FramePadding.y * 2.0f) / 2.0f - icon_size / 2.0f;

    auto style = ImGui::GetStyle();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);
    ImGui::Image(ICON_OBJECT);
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - height);
    if (ImGui::InputText("Name", &buffer, ImGuiInputTextFlags_EnterReturnsTrue))
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