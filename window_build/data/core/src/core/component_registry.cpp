#include "core/component_registry.hpp"

void ComponentRegistry::register_component(const std::string &name, Function<Shared<Component>()> factory)
{
    factories[name] = factory;
}

Shared<Component> ComponentRegistry::create_component(const std::string &name) const
{
    auto it = factories.find(name);
    if (it != factories.end())
    {
        return it->second();
    }

    return nullptr;
}