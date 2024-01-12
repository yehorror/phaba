#pragma once

#include <vector>
#include <span>
#include <GL/glew.h>
#include <Program/Program.hpp>
#include <Buffer/Buffer.hpp>
#include "Common.hpp"
#include "Body/Body.hpp"
#include "BodyPart/BodyPart.hpp"
#include "Detail/Engine.hpp"

namespace Phaba
{
    class World
    {
    public:
        explicit World(Vector2 freeFallAcceleration = {});

        Body CreateBody(const BodyDef& def);

        // BodyPart CreateBodyPart(std::span<Vector2> vertices);

        void Step(TimeDelta timeDelta);

    private:
        Detail::Engine m_engine;
    };
}