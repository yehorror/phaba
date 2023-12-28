#pragma once

#include <vector>
#include <GL/glew.h>
#include <Program/Program.hpp>
#include <Buffer/Buffer.hpp>
#include "Common.hpp"
#include "Body/Body.hpp"
#include "Detail/Engine.hpp"

namespace Phaba
{
    class World
    {
    public:
        explicit World(Vector2 freeFallAcceleration = {});

        Body CreateBody(const BodyDef& def);

        void Step(TimeDelta timeDelta);

    private:
        Detail::Engine m_engine;
    };
}