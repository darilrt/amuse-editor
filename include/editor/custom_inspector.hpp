#pragma once

#include <types.hpp>

class CustomInspector
{
public:
    Function<void()> on_inspector;
    Function<void()> on_scene_gui;
};