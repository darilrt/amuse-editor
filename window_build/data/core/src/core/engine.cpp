#include "core/engine.hpp"
#include "logger.hpp"

#include "core/components/transform.hpp"
#include "core/components/missing_component.hpp"

Engine::Engine()
{
    logger = new_unique<Logger>();

    asset_manager = new_unique<AssetManager>();
    asset_manager->engine = this;

    reset_component_registry();

    graphic_manager = new_unique<GraphicManager>();
}

void Engine::load_actor(const std::filesystem::path &path)
{
    auto actor = asset_manager->get<Actor>(path);

    if (!actor)
    {
        logger->error("Failed to load actor: {}", path.string());
        return;
    }

    actor->engine = this;

    root_actor = std::move(actor);
}

void Engine::reset_component_registry()
{
    component_registry = new_unique<ComponentRegistry>();

    component_registry->register_component<MissingComponent>("MissingComponent");
    component_registry->register_component<Transform>("Transform");
}