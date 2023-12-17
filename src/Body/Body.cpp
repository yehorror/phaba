#include "Body.hpp"
#include "World/World.hpp"

namespace Phaba
{
    Body::Body(World& world, unsigned int index)
        : m_world(world)
        , m_index(index)
    {
    }

    Vector2 Body::GetVelocity() const
    {
        return m_world.GetVelocity(m_index);
    }

    void Body::SetVelocity(Vector2 velocity)
    {
        // m_velocity = velocity;
    }
}