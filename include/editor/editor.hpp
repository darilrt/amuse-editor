#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>

#include <core.hpp>
#include <types.hpp>

#include "editor/editor_window.hpp"
#include "loader.hpp"

struct EditorWindowState
{
    bool is_open = true;
    Shared<EditorWindow> window;
};

struct EditorPreferences
{
    std::string external_editor = "code";
};

class Editor
{
public:
    Window window;
    Shared<Actor> selected_actor;
    std::filesystem::path workspace_path;
    std::filesystem::path current_project_path;
    Engine *engine;
    std::unordered_map<std::string, EditorWindowState> windows;
    Function<void(Editor *editor)> status_callback;
    EditorPreferences preferences;

    Unique<Loader> loader;
    uint64_t loader_dll_stamp;

    Editor();

    template <typename T>
    void register_window(const std::string &name)
    {
        windows[name] = {};
        windows[name].is_open = true;
        windows[name].window = Shared<EditorWindow>(new T());
        windows[name].window->name = name;
        windows[name].window->editor = this;
        windows[name].window->on_init();
    }

    template <typename T>
    Shared<T> get_window(const std::string &name)
    {
        return std::static_pointer_cast<T>(windows[name].window);
    }

    void create_project(const std::filesystem::path &path);

    void open_project(const std::filesystem::path &path);

    void load_components();

    void check_components_reload();

    void open(const std::filesystem::path &path);

    void load_actor(const std::filesystem::path &path);

    void main_menu_bar();

    void run();

    void set_edited(bool edited = true);

    void set_status(Function<void(Editor *editor)> callback);
};