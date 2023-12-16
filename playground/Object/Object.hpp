#pragma once

#include "../Shape/Shape.hpp"
#include <glm/vec2.hpp>

namespace Playground
{
    struct Object
    {
        Playground::Shape& shape;
        glm::vec2 position;
        float angle;
    };
}