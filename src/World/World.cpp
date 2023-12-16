#include "World.hpp"

namespace Phaba
{
    World::World(Vector2 freeFallAcceleration)
        : m_freeFallAcceleration(std::move(freeFallAcceleration))
    {
    }

    Body World::CreateBody()
    {
        return Body{};
    }

    void World::Step(TimeDelta timeDelta)
    {
    }
}