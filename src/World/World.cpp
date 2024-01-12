#include "World.hpp"
#include <stdexcept>
#include <string_view>

namespace Phaba
{
    World::World(Vector2 freeFallAcceleration)
        : m_engine(freeFallAcceleration)
    {
    }

    Body World::CreateBody(const BodyDef& def)
    {
        return m_engine.CreateBody(def);
    }

    /*
    BodyPart World::CreateBodyPart(std::span<Vector2> vertices)
    {
        return m_engine.CreateBodyPart(vertices);
    }
    */

    void World::Step(TimeDelta timeDelta)
    {
        m_engine.Step(timeDelta);
    }
}