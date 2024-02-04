#pragma once

#include <glm/vec2.hpp>

namespace Phaba
{
    using TimeDelta = float;
    using Vector2 = glm::vec2;

    namespace Detail
    {
        struct VerticesIndices
        {
            unsigned int start;
            unsigned int end;
        };
    }
}