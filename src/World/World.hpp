#pragma once

#include <vector>
#include <GL/glew.h>
#include "Common.hpp"
#include "Body/Body.hpp"

namespace Phaba
{
    class World
    {
    public:
        explicit World(Vector2 freeFallAcceleration = {});

        Body& CreateBody();

        Vector2 GetVelocity(unsigned int index) const;

        void Step(TimeDelta timeDelta);

    private:
        Vector2 m_freeFallAcceleration;
        std::vector<Body> m_bodiesVec;

        GLuint m_computeProgram{};
        GLuint m_bodies{};
    };
}