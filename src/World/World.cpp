#include "World.hpp"
#include <stdexcept>
#include <string_view>

namespace Phaba
{
    World::World(Vector2 freeFallAcceleration)
        : m_engine(freeFallAcceleration)
    {
    }

    BodyBuilder World::MakeBodyBuilder()
    {
        return BodyBuilder(m_engine);
    }

    BodyPart World::CreateBodyPart(std::span<const Vector2> vertices)
    {
        return m_engine.CreateBodyPart(vertices);
    }

    void World::Step(TimeDelta timeDelta)
    {
        m_engine.Step(timeDelta);
    }
}