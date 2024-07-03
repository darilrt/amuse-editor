#pragma once

#include <core.hpp>

class DebugComponent : public Component
{
public:
    DebugComponent();

    void on_start() override;

    void on_update() override;
};