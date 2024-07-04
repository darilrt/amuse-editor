#pragma once
#pragma once

#include <types.hpp>

#include "editor/editor_window.hpp"
#include "editor/custom_inspector.hpp"

class InspectorEditor : public EditorWindow
{
public:
    std::unordered_map<std::string, Shared<CustomInspector>> custom_inspectors;

    void on_init() override;

    void on_gui() override;

    template <typename T>
    void register_custom_inspector(const std::string &name)
    {
        constexpr bool has_on_inspector = requires(const T &t) {
            T::on_inspector();
        };

        Shared<CustomInspector> inspector = new_shared<CustomInspector>();

        if constexpr (has_on_inspector)
        {
            inspector->on_inspector = T::on_inspector;
        }

        constexpr bool has_on_scene_gui = requires(const T &t) {
            T::on_scene_gui();
        };

        if constexpr (has_on_scene_gui)
        {
            inspector->on_scene_gui = T::on_scene_gui;
        }

        custom_inspectors[name] = inspector;
    }

    Shared<CustomInspector> get_custom_inspector(const std::string &name)
    {
        auto it = custom_inspectors.find(name);
        if (it != custom_inspectors.end())
        {
            return it->second;
        }

        return nullptr;
    }
};
