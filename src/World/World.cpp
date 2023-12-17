#include "World.hpp"

namespace Phaba
{
    World::World(Vector2 freeFallAcceleration)
        : m_freeFallAcceleration(std::move(freeFallAcceleration))
    {
    }

    Body& World::CreateBody()
    {
        return m_bodies.emplace_back();
    }

    void World::Step(TimeDelta timeDelta)
    {
        for (auto& body : m_bodies)
        {
            body.SetVelocity(body.GetVelocity() + m_freeFallAcceleration * timeDelta);
        }
    }
}