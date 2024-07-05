#pragma once

#include <dll.hpp>
#include <core.hpp>

#define REGISTER_COMPONENT(C) engine->component_registry->register_component<C>(#C)

#define COMPONENTS void loader(Engine *engine)

extern "C" AMUSE_API void loader(Engine *engine);