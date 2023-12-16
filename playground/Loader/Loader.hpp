#pragma once

#include <vector>
#include <filesystem>
#include <glm/vec2.hpp>

namespace Playground
{
    std::vector<glm::vec2> LoadShape(std::filesystem::path path);
}