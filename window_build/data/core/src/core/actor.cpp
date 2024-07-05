#include "toml.hpp"

#include "logger.hpp"
#include "core/actor.hpp"
#include "core/engine.hpp"

void Actor::start()
{
    for (auto &component : components)
    {
        component->on_start();
    }

    for (auto &child : children)
    {
        child->start();
    }
}

void Actor::update()
{
    for (auto &component : components)
    {
        component->on_update();
    }

    for (auto &child : children)
    {
        child->update();
    }
}

Shared<Actor> load_actor_helper(const toml::value &data, Engine *engine)
{
    Shared<Actor> actor = new_shared<Actor>();

    if (data.contains("name"))
        actor->name = toml::find<std::string>(data, "name");

    if (data.contains("path"))
        actor->path = toml::find<std::string>(data, "path");

    if (!actor->path.empty())
        logger.info("Loading actor: {}", actor->path);

    if (data.contains("components"))
    {
        auto components = toml::find(data, "components");

        for (auto &component_data : components.as_array())
        {
            std::string component_name = toml::find<std::string>(component_data, "name");
            Shared<Component> component = engine->component_registry->create_component(component_name);

            if (component == nullptr)
            {
                component = engine->component_registry->create_component("MissingComponent");

                assert(component != nullptr); // MissingComponent must be registered
            }

            actor->add_component(component);
        }
    }

    if (data.contains("children"))
    {
        auto children = toml::find(data, "children");

        for (auto &child_data : children.as_array())
        {
            Shared<Actor> child = load_actor_helper(child_data, engine);
            child->parent = actor;
            child->engine = actor->engine;
            actor->children.push_back(child);
        }
    }

    return actor;
}

Shared<Actor> Actor::load(const std::filesystem::path &path, Engine *engine)
{
    auto data = toml::parse(path.string());

    Shared<Actor> actor = load_actor_helper(data, engine);
    actor->path = path.string();

    return actor;
}

void save_actor_helper(Actor *actor, toml::value &data)
{
    data["name"] = actor->name;
    data["path"] = actor->path;

    data["components"] = toml::array{};

    for (auto &component : actor->components)
    {
        toml::value component_data;
        component_data["name"] = component->_name;

        data["components"].push_back(component_data);
    }

    if (actor->children.size() == 0)
        return;

    data["children"] = toml::array{};

    for (auto &child : actor->children)
    {
        toml::value child_data;
        save_actor_helper(child.get(), child_data);
        data["children"].push_back(child_data);
    }
}

void Actor::save()
{
    toml::value data;

    save_actor_helper(this, data);

    std::ofstream file(path);
    file << data;
    file.close();
}

AMUSE_API void Actor::add_component(Shared<Component> component)
{
    component->actor = this;
    components.push_back(component);
}

AMUSE_API Shared<Component> Actor::get_component(const std::string &name)
{
    for (auto &component : components)
    {
        if (component->_name == name)
            return component;
    }

    return nullptr;
}

AMUSE_API void Actor::remove_component(Shared<Component> component)
{
    auto it = std::find(components.begin(), components.end(), component);

    if (it != components.end())
        components.erase(it);
}