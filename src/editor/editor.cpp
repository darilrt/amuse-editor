#include <fstream>

#include <SDL2/SDL.h>

#include "editor/editor.hpp"
#include "core/event_system.hpp"
#include "core/input.hpp"
#include "editor/style.hpp"

#include "core/gfx.hpp"
#include "loader.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "editor/windows/hierarchy.hpp"
#include "editor/windows/files.hpp"
#include "editor/windows/scene.hpp"
#include "editor/windows/inspector.hpp"
#include "editor/windows/preferences.hpp"
#include "visual_editor/visual_component.hpp"

#include "icons.hpp"

Editor::Editor() : window("Amuse Editor", 1280, 720)
{
    logger.name = "AMUSE";
    workspace_path = "C:/amuse/projects";
    current_project_path = "";

    if (!std::filesystem::exists(workspace_path))
    {
        std::filesystem::create_directories(workspace_path);
    }

    loader = new_unique<Loader>();
}

void Editor::create_project(const std::filesystem::path &path)
{
    std::filesystem::create_directory(path);
    std::filesystem::create_directory(path / "assets");
}

void Editor::open_project(const std::filesystem::path &path)
{
    set_status([this, path](Editor *editor)
               { ImGui::Text("Opening project %s", path.string().c_str()); });

    current_project_path = path;

    load_components();

    set_status([this](Editor *editor)
               { ImGui::Text("Project loaded"); });
}

void Editor::load_components()
{
    auto copy_file = [](const std::filesystem::path &from, const std::filesystem::path &to)
    {
        std::ifstream src(from, std::ios::binary);
        std::ofstream dst(to, std::ios::binary);

        dst.clear();

        dst << src.rdbuf();
    };

    engine->reset_component_registry();

    loader->free();

    auto from_dll_path = current_project_path / "build" / "libTestProject.dll";
    auto dll_path = current_project_path / "build" / "components.dll";

    if (!std::filesystem::exists(from_dll_path))
    {
        return;
    }

    copy_file(from_dll_path, dll_path);

    loader->load(dll_path.string().c_str());

    typedef void (*FuncType)(Engine *);

    auto func = (FuncType)loader->get_function<FuncType>("loader");

    if (!func)
    {
        logger.error("Failed to load components");
        return;
    }

    func(engine);

    loader_dll_stamp = std::filesystem::last_write_time(from_dll_path).time_since_epoch().count();

    set_status([this](Editor *editor)
               { ImGui::Text("Components reloaded"); });
}

void Editor::check_components_reload()
{
    const auto from_dll_path = current_project_path / "build" / "libTestProject.dll";

    auto stamp = std::filesystem::last_write_time(from_dll_path).time_since_epoch().count();

    if (stamp != loader_dll_stamp)
    {
        set_status(
            [this](Editor *editor)
            {
                ImGui::SetNextItemWidth(ImGui::GetWindowWidth());
                ImGui::ProgressBar(-1.0f * (float)ImGui::GetTime(), ImVec2(0.0f, 0.0f), "Loading components..");
            });

        logger.info("Reloading components");
        load_components();
    }
}

void Editor::open(const std::filesystem::path &path)
{
    logger.info("Opening: {}", path.string());
    if (std::filesystem::is_directory(path) || !std::filesystem::exists(path))
    {
        return;
    }

    std::string ext = path.extension().string();

    if (ext == ".actor")
    {
        load_actor(path);

        if (engine->root_actor != nullptr)
        {
            window.set_title("Amuse Editor - " + engine->root_actor->name);
        }

        selected_actor = engine->root_actor;
    }
    else if (ext == ".cpp" || ext == ".h")
    {
        system(("code " + path.string()).c_str());
    }
    else
    {
        // Open in default editor
    }
}

void Editor::load_actor(const std::filesystem::path &path)
{
    engine->load_actor(path);
    set_edited(false);
    set_status([this](Editor *editor)
               { ImGui::Text("Loaded %s", engine->root_actor->path.c_str()); });
}

void Editor::main_menu_bar()
{
    static struct
    {
        bool open_new_project = false;
        bool open_project = false;
    } state;

    state = {};

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Project", "Ctrl+N"))
            {
                state.open_new_project = true;
            }

            if (ImGui::MenuItem("Open Project", "Ctrl+O"))
            {
                state.open_project = true;
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Preferences"))
            {
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit"))
            {
                window.quit();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows"))
        {
            for (auto &pair : windows)
            {
                if (ImGui::MenuItem(pair.first.c_str(), NULL, pair.second.is_open))
                {
                    pair.second.is_open = !pair.second.is_open;
                }
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (state.open_new_project)
    {
        ImGui::OpenPopup("New Project");
    }

    if (ImGui::BeginPopupModal("New Project", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        static char project_name[128] = "";
        ImGui::Image(ICON_FOLDER);
        ImGui::SameLine();
        ImGui::InputText("Project Name", project_name, IM_ARRAYSIZE(project_name));

        if (ImGui::Button("Create", ImVec2(120, 0)))
        {
            std::filesystem::path project_path = workspace_path / project_name;

            create_project(project_path);

            project_name == "";

            open_project(project_path);

            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    if (state.open_project)
    {
        ImGui::OpenPopup("Open Project");
    }

    if (ImGui::BeginPopupModal("Open Project", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup))
    {
        std::vector<char *> projects;

        for (auto &entry : std::filesystem::directory_iterator(workspace_path))
        {
            if (entry.is_directory())
            {
                projects.push_back((char *)entry.path().string().c_str());
            }
        }

        static int item_current = 0;

        ImGui::ListBox("Projects", &item_current, projects.data(), projects.size());

        if (ImGui::Button("Open", ImVec2(120, 0)))
        {
            open_project(projects[item_current]);
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void Editor::run()
{
    engine = new Engine();

    window.set_resizable(true);
    // window.maximize();
    window.set_vsync(VSync::On);

    EventSystem es;
    Input input(es);

    gfx::init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplSDL2_InitForOpenGL((SDL_Window *)window.sdl_window, window.gl_context);

    auto glsl_version = "#version 150";
    ImGui_ImplOpenGL3_Init(glsl_version);

    style_imgui();
    load_icons_texture();

    // Regist native windows
    register_window<HierarchyEditor>("Hierarchy");
    register_window<FilesEditor>("Files");
    register_window<SceneEditor>("Scene");
    register_window<InspectorEditor>("Inspector");
    register_window<PreferencesEditor>("Preferences");
    register_window<VisualComponentEditor>("Visual Component");

    /// DEBUG PROPOSAL
    open_project("C:/amuse/projects/Test");

    while (window.is_open)
    {
        gfx::clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        window.poll_events(es);

        check_components_reload();

        if (ImGui::Shortcut(ImGuiMod_Ctrl + ImGuiKey_S, ImGuiInputFlags_RouteAlways))
        {
            logger.info("Saving project");

            if (engine->root_actor != nullptr)
            {
                set_status([](Editor *editor)
                           { ImGui::Text("Saving..."); });
                engine->root_actor->save();
                set_edited(false);
                set_status([this](Editor *editor)
                           { ImGui::Text("Saved %s", engine->root_actor->path.c_str()); });
            }
        }

        static bool show_demo_window = false;

        if (ImGui::Shortcut(ImGuiKey_F1, ImGuiInputFlags_RouteAlways))
            show_demo_window = !show_demo_window;

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        main_menu_bar();

        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - ImGui::GetFrameHeight()));

        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags windowFlags =
            ImGuiWindowFlags_MenuBar |
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus;

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.08f, 0.08f, 1.00f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Editor", 0, windowFlags);

        ImGuiID dockspace_id = ImGui::GetID("Editor");
        ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_NoWindowMenuButton;
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);

        if (!ImGui::DockBuilderGetNode(dockspace_id))
        {
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_None);

            ImGuiID dock_main_id = dockspace_id;

            ImGuiID dock_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
            ImGuiID dock_right_down = ImGui::DockBuilderSplitNode(dock_right, ImGuiDir_Down, 0.7f, nullptr, &dock_right);
            ImGuiID dock_down = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.7f, nullptr, &dock_main_id);

            ImGui::DockBuilderDockWindow("Scene", dock_main_id);
            ImGui::DockBuilderDockWindow("Hierarchy", dock_right);
            ImGui::DockBuilderDockWindow("Inspector", dock_right_down);

            ImGui::DockBuilderFinish(dock_main_id);
        }

        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
        float height = ImGui::GetFrameHeight();

        if (ImGui::BeginViewportSideBar("##StatusBar", NULL, ImGuiDir_Down, height, window_flags))
        {
            if (ImGui::BeginMenuBar())
            {
                if (status_callback)
                {
                    status_callback(this);
                }
                ImGui::EndMenuBar();
            }
            ImGui::End();
        }

        for (auto &pair : windows)
        {
            pair.second.window->on_push_style();

            if (pair.second.is_open)
            {
                ImGui::Begin(pair.second.window->name.c_str(), &pair.second.is_open);
                pair.second.window->on_gui();
                ImGui::End();
            }

            pair.second.window->on_pop_style();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.swap_buffers();
    }
}

void Editor::set_edited(bool edited)
{
    std::string title = "Amuse Editor";

    if (engine->root_actor != nullptr)
    {
        title += " - " + engine->root_actor->name;
    }

    if (edited)
    {
        window.set_title(title + " *");
    }
    else
    {
        window.set_title(title);
    }
}

void Editor::set_status(Function<void(Editor *editor)> callback)
{
    status_callback = callback;
}
