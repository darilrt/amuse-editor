#pragma once

#include "core/gfx/gl.hpp"
#include "types.hpp"

class Texture
{
public:
    gfx::Image image;
    gfx::Sampler sampler;

    AMUSE_API Texture(
        int width,
        int height,
        gfx::TextureFormat format,
        gfx::SamplerFilter min_filter,
        gfx::SamplerFilter mag_filter,
        gfx::SamplerWrap wrap_s,
        gfx::SamplerWrap wrap_t) : image(width, height, format), sampler(min_filter, mag_filter, wrap_s, wrap_t) {}

    static AMUSE_API Shared<Texture> from_file(const char *path, gfx::SamplerFilter min_filter, gfx::SamplerFilter mag_filter, gfx::SamplerWrap wrap_s, gfx::SamplerWrap wrap_t);
};