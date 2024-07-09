#pragma once

#include <core.hpp>

class CustomInspector
{
public:
    Function<void(Component *)> on_inspector;
    Function<void(Component *)> on_scene_gui;
};