#include "editor/windows/scene.hpp"
#include "imgui/imgui.h"
#include "editor/editor.hpp"
#include "icons.hpp"

void SceneEditor::on_init()
{
    framebuffer = new_unique<gfx::Framebuffer>();
    color = new_unique<gfx::Image>(512, 512, gfx::TextureFormat::RGB);

    auto sampler = gfx::Sampler(
        gfx::SamplerFilter::Linear,
        gfx::SamplerFilter::Linear,
        gfx::SamplerWrap::ClampToEdge,
        gfx::SamplerWrap::ClampToEdge);
    color->_apply_sampler(sampler);

    framebuffer->attach(gfx::AttachmentType::Color0, *color.get());
}

void SceneEditor::on_gui()
{
    auto style = ImGui::GetStyle();

    ImVec2 start = ImGui::GetWindowContentRegionMin();

    static Vec2 old_size = Vec2(0, 0);
    Vec2 size = ImGui::GetWindowContentRegionMax();
    size.x -= ImGui::GetWindowContentRegionMin().x;
    size.y -= ImGui::GetWindowContentRegionMin().y;

    if (old_size != size)
    {
        old_size = size;
    }

    ImGui::SetCursorPos(start);

    const Mat4 &view = Mat4::identity();

    editor->engine->graphic_manager->render(
        view,
        Mat4::perspective(45.0f, 1.0f, 0.1f, 100.0f),
        *framebuffer.get());

    ImGui::Image(reinterpret_cast<void *>(color->id), size, ImVec2(0, 0), ImVec2(1, 1));

    start.x += 10;
    start.y += 10;
    ImGui::SetCursorPos(start);

    if (ImGui::ImageButton(ICON_PLACEHOLDER))
    {
    }

    ImGui::SameLine();

    if (ImGui::ImageButton(ICON_PLACEHOLDER))
    {
    }

    ImGui::SameLine();

    if (ImGui::ImageButton(ICON_PLACEHOLDER))
    {
    }
}

void SceneEditor::on_push_style()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void SceneEditor::on_pop_style()
{
    ImGui::PopStyleVar();
}