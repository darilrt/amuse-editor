#include "editor/windows/hierarchy.hpp"
#include "editor/editor.hpp"
#include "imgui/imgui.h"
#include "icons.hpp"

void hierarchy_context_menu_helper(Shared<Actor> actor, Editor *editor)
{
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Add child"))
        {
            Shared<Actor> new_actor = new_shared<Actor>();
            new_actor->name = "New Actor";
            new_actor->parent = actor;
            actor->children.push_back(new_actor);
            editor->selected_actor = new_actor;

            editor->set_edited();
        }

        if (ImGui::MenuItem("Remove"))
        {
            if (editor->selected_actor == actor)
            {
                editor->selected_actor = nullptr;
            }

            if (actor->parent != nullptr)
            {
                actor->parent->children.erase(std::remove(actor->parent->children.begin(), actor->parent->children.end(), actor), actor->parent->children.end());
            }
            else
            {
                editor->engine->root_actor = nullptr;
            }

            editor->set_edited();
        }

        ImGui::EndPopup();
    }
}

void draw_actor_tree(Shared<Actor> actor, Editor *editor)
{
    if (actor == nullptr)
        return;

    const bool has_children = !actor->children.empty();

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen;

    if (!has_children)
        flags |= ImGuiTreeNodeFlags_Leaf;

    const bool is_selected = editor->selected_actor == actor;

    if (is_selected)
        flags |= ImGuiTreeNodeFlags_Selected;

    ImGui::PushID(actor.get());
    const bool is_open = ImGui::TreeNodeEx(actor->name.c_str(), flags);

    hierarchy_context_menu_helper(actor, editor);

    if (ImGui::IsItemClicked())
    {
        editor->selected_actor = actor;
    }

    ImGui::PopID();
    if (is_open)
    {
        for (auto &child : actor->children)
        {
            draw_actor_tree(child, editor);
        }

        ImGui::TreePop();
    }
}

void HierarchyEditor::on_init()
{
}

void HierarchyEditor::on_gui()
{

    if (editor->engine->root_actor == nullptr)
    {
        ImGui::Text("No actor loaded");
        return;
    }

    draw_actor_tree(editor->engine->root_actor, editor);
}