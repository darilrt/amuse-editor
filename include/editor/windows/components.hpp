#pragma once

#include "editor/editor_window.hpp"

class AssetsEditor : public EditorWindow
{
public:
    void on_init() override;

    void on_gui() override;
};