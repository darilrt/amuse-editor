#pragma once

#include <vector>
#include <filesystem>

#include "core/component.hpp"
#include "types.hpp"
#include "dll.hpp"

class Engine;

class Actor
{
public:
    Engine *engine;
    std::string name = "Empty Actor";
    std::string path = "";

    std::vector<Shared<Component>> components;
    Shared<Actor> parent;
    std::vector<Shared<Actor>> children;

    AMUSE_API void start();

    AMUSE_API void update();

    AMUSE_API Shared<Actor> load(const std::filesystem::path &path, Engine *engine);

    AMUSE_API void save();

    AMUSE_API void add_component(Shared<Component> component);

    AMUSE_API Shared<Component> get_component(const std::string &name);

    AMUSE_API void remove_component(Shared<Component> component);
};