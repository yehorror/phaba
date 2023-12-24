#pragma once

#include <vector>
#include <GL/glew.h>
#include <Program/Program.hpp>
#include <Buffer/Buffer.hpp>
#include "Common.hpp"
#include "Body/Body.hpp"

namespace Phaba
{
    class World
    {
    public:
        explicit World(Vector2 freeFallAcceleration = {});

        Body CreateBody(Phaba::BodyType type = Phaba::BodyType::kDynamic);

        Vector2 GetVelocity(unsigned int index) const;
        Vector2 GetPosition(unsigned int index) const;

        void Step(TimeDelta timeDelta);

    private:
        Vector2 m_freeFallAcceleration;

        GL::Program m_computeProgram;
        GL::Buffer m_bodiesBuffer;
    };
}