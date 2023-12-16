#pragma once

#include <vector>
#include <filesystem>
#include "Scene/Scene.hpp"
#include "Storage/Storage.hpp"

namespace Playground
{
    class Loader
    {
    public:
        Scene LoadScene(std::filesystem::path path);

    private:
        Object LoadObject(std::filesystem::path path);

    private:
        Storage m_storage;
    };
}