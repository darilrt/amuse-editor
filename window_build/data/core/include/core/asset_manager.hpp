#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <tuple>

#include "dll.hpp"
#include "types.hpp"

class Engine;

class AssetManager
{
public:
    Engine *engine;
    std::filesystem::path asset_dir = "";

    template <typename T>
    Shared<T> get(const std::filesystem::path &name)
    {
        T asset;
        return asset.load(asset_dir / name, engine);
    }
};