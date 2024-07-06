#pragma once

#include "core/gfx/texture.hpp"
#include "types.hpp"

extern Shared<Texture> icons_texture;
extern float icon_size;

void load_icons_texture();

#define ICON_ARROW_DOWN reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.0, 1.0), ImVec2(0.14285714285714285f, 0.0)

#define ICON_ARROW_RIGHT reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.14285714285714285f, 1.0), ImVec2(0.2857142857142857f, 0.0)

#define ICON_CPP reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.2857142857142857, 1.0), ImVec2(0.42857142857142855, 0.0)

#define ICON_CROSS reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.42857142857142855, 1.0), ImVec2(0.5714285714285714, 0.0)

#define ICON_FOLDER reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.5714285714285714, 1.0), ImVec2(0.7142857142857143, 0.0)

#define ICON_OBJECT reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.7142857142857143, 1.0), ImVec2(0.8571428571428571, 0.0)

#define ICON_PLACEHOLDER reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.8571428571428571, 1.0), ImVec2(1.0, 0.0)
