#include "Body.hpp"
#include "World/Detail/Engine.hpp"

namespace Phaba
{
    Body::Body(Detail::Engine& engine, unsigned int index)
        : m_engine(engine)
        , m_index(index)
    {
    }

    Vector2 Body::GetVelocity() const
    {
        return m_engine.GetVelocity(m_index);
    }

    Vector2 Body::GetPosition() const
    {
        return m_engine.GetPosition(m_index);
    }
}