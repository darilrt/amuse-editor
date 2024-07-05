#pragma once

#include <string>

#include "dll.hpp"

class Actor;

class Component
{
public:
    Actor *actor;
    bool enabled = true;
    std::string _name;

    virtual AMUSE_API void on_start() {}

    virtual AMUSE_API void on_update() {}
};