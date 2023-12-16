#include "Body.hpp"

namespace Phaba
{
    Vector2 Body::GetVelocity() const
    {
        return m_velocity;
    }

    void Body::SetVelocity(Vector2 velocity)
    {
        m_velocity = velocity;
    }
}