#include "icons.hpp"

Shared<Texture> icons_texture;
float icon_size = 20.0f;

void load_icons_texture()
{
    icons_texture = Texture::from_file(
        "data/icons/icons.png",
        gfx::SamplerFilter::Linear,
        gfx::SamplerFilter::Linear,
        gfx::SamplerWrap::ClampToEdge,
        gfx::SamplerWrap::ClampToEdge);
}