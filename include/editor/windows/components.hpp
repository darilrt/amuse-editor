#pragma once

#include "editor/editor_window.hpp"

class ComponentsEditor : public EditorWindow
{
public:
    void on_init() override;

    void on_gui() override;
};