#include "Body.hpp"
#include "Detail/Bodies/Bodies.hpp"

namespace Phaba
{
    Body::Body(Detail::Bodies& bodies, unsigned int index)
        : m_bodies(bodies)
        , m_index(index)
    {
    }

    Vector2 Body::GetVelocity() const
    {
        return m_bodies.GetVelocity(m_index);
    }

    Vector2 Body::GetPosition() const
    {
        return m_bodies.GetPosition(m_index);
    }

    float Body::GetAngle() const
    {
        return m_bodies.GetAngle(m_index);
    }
}