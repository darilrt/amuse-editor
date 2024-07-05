#pragma once

#include "core/actor.hpp"
#include "core/component_registry.hpp"
#include "core/asset_manager.hpp"
#include "core/graphic_manager.hpp"
#include "logger.hpp"
#include "types.hpp"
#include "dll.hpp"

class Engine
{
public:
    Unique<Logger> logger;
    Shared<Actor> root_actor;
    Unique<AssetManager> asset_manager;
    Unique<ComponentRegistry> component_registry;
    Unique<GraphicManager> graphic_manager;

    AMUSE_API Engine();

    AMUSE_API void load_actor(const std::filesystem::path &path);

    AMUSE_API void reset_component_registry();
};
