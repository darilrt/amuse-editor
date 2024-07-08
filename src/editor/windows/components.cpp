#include <core.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "editor/windows/components.hpp"
#include "editor/editor.hpp"
#include "editor/ui.hpp"
#include "icons.hpp"

void AssetsEditor::on_init()
{
}

void AssetsEditor::on_gui()
{
    auto style = ImGui::GetStyle();
    Vec2 size = ImGui::GetContentRegionAvail();
    Vec2 pos = ImGui::GetCursorPos();

    if (ui::TreeNodeFileExplorer(ICON_FOLDER, "Actors"))
    {
        ui::TreeNodeFileExplorer(ICON_OBJECT, "MainMenu", true);
        ui::TreeNodeFileExplorer(ICON_OBJECT, "Player", true);

        if (ui::TreeNodeFileExplorer(ICON_FOLDER, "Components"))
        {
            ui::TreeNodeFileExplorer(ICON_CPP, "TestComponent", true);
            ui::TreeNodeFileExplorer(ICON_CPP, "PlayerController", true);
            ui::TreeNodeFileExplorer(ICON_CPP, "CameraController", true);
            ImGui::TreePop();
        }

        ImGui::TreePop();
    }
}