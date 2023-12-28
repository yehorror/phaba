#pragma once

#include <vector>
#include <filesystem>
#include "GenericScene/GenericScene.hpp"
#include "Storage/Storage.hpp"

namespace Playground
{
    class Loader
    {
    public:
        GenericScene LoadScene(std::filesystem::path path);

    private:
        Object LoadObject(std::filesystem::path path);

    private:
        Storage m_storage;
    };
}