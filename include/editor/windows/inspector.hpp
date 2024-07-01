#pragma once
#pragma once

#include "editor/editor_window.hpp"

class InspectorEditor : public EditorWindow
{
public:
    void on_init() override;

    void on_gui() override;
};
