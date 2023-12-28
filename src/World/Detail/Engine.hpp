#pragma once

#include "Common.hpp"
#include "Program/Program.hpp"
#include "Buffer/Buffer.hpp"
#include "Body/Body.hpp"

namespace Phaba::Detail
{
    class Engine
    {
    public:
        explicit Engine(Vector2 freeFallAcceleration);

        Body CreateBody(const BodyDef& def);

        Vector2 GetVelocity(unsigned int index) const;
        Vector2 GetPosition(unsigned int index) const;

        void Step(TimeDelta time);

    private:
        GL::Program m_computeProgram;
        GL::Buffer m_bodiesBuffer;
    };
}