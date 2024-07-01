#include "editor/windows/preferences.hpp"
#include "editor/editor.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

void PreferencesEditor::on_init()
{
}

void PreferencesEditor::on_gui()
{
    if (ImGui::BeginTabBar("MyTabBar"))
    {
        if (ImGui::BeginTabItem("General"))
        {
            ImGui::Text("General settings");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Editor"))
        {
            ImGui::Text("Editor settings");

            ImGui::Text("External editor:");
            ImGui::SameLine();

            ImGui::InputText("##external_editor", &editor->preferences.external_editor);

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Shortcuts"))
        {
            ImGui::Text("Shortcuts settings");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}
