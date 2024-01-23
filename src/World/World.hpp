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
#include "BodyBuilder/BodyBuilder.hpp"

namespace Phaba
{
    class World
    {
    public:
        explicit World(Vector2 freeFallAcceleration = {});

        BodyBuilder MakeBodyBuilder();

        BodyPart CreateBodyPart(std::span<Vector2> vertices);

        void Step(TimeDelta timeDelta);

    private:
        Detail::Engine m_engine;
    };
}