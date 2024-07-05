#pragma once

#include <string>
#include <functional>
#include <unordered_map>

#include "core/component.hpp"
#include "types.hpp"
#include "dll.hpp"

class ComponentRegistry
{
public:
    std::unordered_map<std::string, Function<Shared<Component>()>> factories;

    AMUSE_API void register_component(const std::string &name, Function<Shared<Component>()> factory);

    AMUSE_API Shared<Component> create_component(const std::string &name) const;

    template <typename T>
    void register_component(const std::string &name)
    {
        register_component(
            name,
            [name]()
            {
                Shared<Component> c = new_shared<T>();
                c->_name = name;
                return c;
            });
    }
};