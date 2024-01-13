#pragma once

#include <span>
#include "Common.hpp"
#include "Program/Program.hpp"
#include "Buffer/Buffer.hpp"
#include "Body/Body.hpp"
#include "BodyPart/BodyPart.hpp"
#include "Bodies/Bodies.hpp"

namespace Phaba::Detail
{
    class Engine
    {
    public:
        explicit Engine(Vector2 freeFallAcceleration);

        Body CreateBody(const BodyDef& def);
        // BodyPart CreateBodyPart(std::span<Vector2> vertices);

        void Step(TimeDelta time);

    private:
        GL::Program m_computeProgram;
        Bodies m_bodies;
        GL::Buffer m_worldConfig{ GL_SHADER_STORAGE_BUFFER };
        GL::Buffer m_bodiesParts{ GL_SHADER_STORAGE_BUFFER };
    };
}