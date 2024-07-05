from cairosvg import svg2png

import pygame
import os
import io

ICON_SIZE = 16 * 10
ICON_PADDING = 5

HEADER_TEMPLATE = """\
#pragma once

#include "core/gfx/texture.hpp"
#include "types.hpp"

extern Shared<Texture> icons_texture;
extern float icon_size;

void load_icons_texture();

"""
class UVImage:
    def __init__(self, name, uv):
        self.name = name
        self.uv = uv

def load_icon_as_sf(path):
    with open(path, "rb") as file:
        data = file.read()
        png = svg2png(data)

        return pygame.image.load(io.BytesIO(png))

def get_icons():
    dir = "icons"

    icons = []
    for file in os.listdir(dir):
        if file.endswith(".svg"):
            icons.append(file)

    return icons

def scale_svg(sf, size):
    aspect = sf.get_width() / sf.get_height()
    x = size[0]
    y = size[1] / aspect 
    return pygame.transform.scale(sf, (int(x), int(y)))

def create_centered_surface(sf, size):
    new_sf = pygame.Surface(size, pygame.SRCALPHA)
    new_sf.fill((0, 0, 0, 0))

    x = (size[0] - sf.get_width()) // 2
    y = (size[1] - sf.get_height()) // 2

    new_sf.blit(sf, (x, y))

    return new_sf

def create_padding_surface(sf, padding):
    new_sf = pygame.Surface((sf.get_width() + padding * 2, sf.get_height() + padding * 2), pygame.SRCALPHA)
    new_sf.fill((0, 0, 0, 0))

    new_sf.blit(sf, (padding, padding))

    return new_sf

def generate_header(uvs):
    with open("include/icons.hpp", "w") as file:
        file.write(HEADER_TEMPLATE)
        for uv in uvs:
            icon_name = uv.name.upper().replace("-", "_").replace(" ", "_")
            uv = uv.uv
            file.write(f"#define ICON_{icon_name} reinterpret_cast<void *>(icons_texture->image.id), ImVec2(icon_size, icon_size), ImVec2({uv[0]}, {uv[3]}), ImVec2({uv[2]}, {uv[1]})\n\n")

def convert_icons():
    icons = get_icons()

    if len(icons) == 0:
        return

    icon_width = ICON_SIZE + ICON_PADDING * 2
    icon_height = ICON_SIZE + ICON_PADDING * 2

    width = icon_width * len(icons)
    height = icon_height

    if len(icons) > 20:
        width = icon_width * 20
        height = icon_height * ((len(icons) // 20) + 1)

    end_sf = pygame.Surface((width, height), pygame.SRCALPHA)
    end_sf.fill((0, 0, 0, 0))

    uvs = []

    x, y = 0, 0
    for icon in icons:
        sf = load_icon_as_sf(f"icons/{icon}")
        sf = scale_svg(sf, (ICON_SIZE, ICON_SIZE))
        sf = create_centered_surface(sf, (ICON_SIZE, ICON_SIZE))
        sf = create_padding_surface(sf, ICON_PADDING)

        x_pos = x * icon_width
        y_pos = y * icon_height

        uvs.append(UVImage(
            icon.split(".")[0], 
            [
                x_pos / width, 
                y_pos / height, 
                (x_pos + icon_width) / width, 
                (y_pos + icon_height) / height
            ]
        ))

        end_sf.blit(sf, (x_pos, y_pos))
        
        x += 1

        if x >= 20:
            x = 0
            y += 1
    
    pygame.image.save(end_sf, "data/icons/icons.png")

    generate_header(uvs)

if __name__ == "__main__":
    convert_icons()
