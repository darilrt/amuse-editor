#pragma once

#include <core.hpp>

class @name : public Component
{
public:
    @name() = default;

    void on_start() override;

    void on_update() override;
};