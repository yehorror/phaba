#pragma once

#include <span>
#include "Common.hpp"
#include "Program/Program.hpp"
#include "Buffer/Buffer.hpp"
#include "Body/Body.hpp"
#include "BodyPart/BodyPart.hpp"

namespace Phaba::Detail
{
    class Engine
    {
    public:
        explicit Engine(Vector2 freeFallAcceleration);

        Body CreateBody(const BodyDef& def);
        // BodyPart CreateBodyPart(std::span<Vector2> vertices);

        Vector2 GetVelocity(unsigned int index) const;
        Vector2 GetPosition(unsigned int index) const;

        void Step(TimeDelta time);

    private:
        GL::Program m_computeProgram;
        GL::Buffer m_bodiesBuffer;
        GL::Buffer m_bodiesParts;
    };
}