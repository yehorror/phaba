#pragma once

#include "Shape/Shape.hpp"
#include "Body/Body.hpp"
#include <glm/vec2.hpp>

namespace Playground
{
    struct Object
    {
        Phaba::Body physicalBody;
        const Playground::Shape& shape;
        glm::vec2 position;
        float angle;
    };
}