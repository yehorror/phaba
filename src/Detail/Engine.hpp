#pragma once

#include <span>
#include "Common.hpp"
#include "Program/Program.hpp"
#include "Buffer/Buffer.hpp"
#include "Body/Body.hpp"
#include "BodyPart/BodyPart.hpp"
#include "Bodies/Bodies.hpp"
#include "Parts/Parts.hpp"

namespace Phaba::Detail
{
    class Engine
    {
    public:
        explicit Engine(Vector2 freeFallAcceleration);

        Body CreateBody(const BodyDef& def);
        BodyPart CreateBodyPart(std::span<const Vector2> vertices);

        void Step(TimeDelta time);

    private:
        GL::Program m_computeProgram;
        GL::Buffer m_worldConfig{ GL_SHADER_STORAGE_BUFFER };
        Bodies m_bodies;
        Parts m_bodiesParts;
    };
}