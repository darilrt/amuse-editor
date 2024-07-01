#pragma once

#include "editor/editor_window.hpp"

class HierarchyEditor : public EditorWindow
{
public:
    void on_init() override;

    void on_gui() override;
};
