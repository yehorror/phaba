#include "World.hpp"
#include <stdexcept>
#include <string_view>

namespace Phaba
{
    World::World(Vector2 freeFallAcceleration)
        : m_engine(freeFallAcceleration)
    {
    }

    Body World::CreateBody(Phaba::BodyType type)
    {
        return m_engine.CreateBody(type);
    }

    void World::Step(TimeDelta timeDelta)
    {
        m_engine.Step(timeDelta);
    }
}