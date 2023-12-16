#pragma once

#include "Common.hpp"
#include "Body/Body.hpp"

namespace Phaba
{
    class World
    {
    public:
        World() = default;
        explicit World(Vector2 freeFallAcceleration);

        Body CreateBody();

        void Step(TimeDelta timeDelta);

    private:
        Vector2 m_freeFallAcceleration;
    };
}