#include "core/gfx/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.hpp"

Shared<Texture> Texture::from_file(const char *path, gfx::SamplerFilter min_filter, gfx::SamplerFilter mag_filter, gfx::SamplerWrap wrap_s, gfx::SamplerWrap wrap_t)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &channels, 0);

    auto format = gfx::TextureFormat::RGBA;

    if (channels == 1)
        format = gfx::TextureFormat::R;
    else if (channels == 2)
        format = gfx::TextureFormat::RG;
    else if (channels == 3)
        format = gfx::TextureFormat::RGB;

    if (data)
    {
        Shared<Texture> tex = new_shared<Texture>(
            width,
            height,
            format,
            min_filter,
            mag_filter,
            wrap_s,
            wrap_t);
        tex->image.set_data(data, width, height, channels);
        tex->image._apply_sampler(tex->sampler);

        stbi_image_free(data);
        return tex;
    }

    return nullptr;
}