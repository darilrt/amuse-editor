#pragma once

#include "core/gfx/texture.hpp"
#include "types.hpp"

extern Shared<Texture> icons_texture;
extern float icon_size;

void load_icons_texture();

#define ICON_ARROW_DOWN reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.0, 1.0), ImVec2(0.1111111111111111, 0.0)

#define ICON_ARROW_RIGHT reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.1111111111111111, 1.0), ImVec2(0.2222222222222222, 0.0)

#define ICON_CPP reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.2222222222222222, 1.0), ImVec2(0.3333333333333333, 0.0)

#define ICON_CROSS reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.3333333333333333, 1.0), ImVec2(0.4444444444444444, 0.0)

#define ICON_CROSS_V2 reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.4444444444444444, 1.0), ImVec2(0.5555555555555556, 0.0)

#define ICON_EMPTY_FILE reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.5555555555555556, 1.0), ImVec2(0.6666666666666666, 0.0)

#define ICON_FOLDER reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.6666666666666666, 1.0), ImVec2(0.7777777777777778, 0.0)

#define ICON_OBJECT reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.7777777777777778, 1.0), ImVec2(0.8888888888888888, 0.0)

#define ICON_PLACEHOLDER reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2(0.8888888888888888, 1.0), ImVec2(1.0, 0.0)

