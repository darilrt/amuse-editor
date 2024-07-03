#include "icons.hpp"

Shared<Texture> icons_texture;
float icon_size = 25.0f;

void load_icons_texture()
{
    icons_texture = Texture::from_file(
        "data/icons/icons.png",
        gfx::SamplerFilter::Nearest,
        gfx::SamplerFilter::Nearest,
        gfx::SamplerWrap::ClampToEdge,
        gfx::SamplerWrap::ClampToEdge);
}