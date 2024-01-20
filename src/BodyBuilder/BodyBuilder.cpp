#include "BodyBuilder.hpp"
#include "World/Detail/Engine.hpp"

namespace Phaba
{
    BodyBuilder::BodyBuilder(Detail::Engine& engine)
        : m_engine(engine)
    {
    }

    BodyBuilder& BodyBuilder::Type(BodyType type)
    {
        m_bodyDef.type = type;
        return *this;
    }

    BodyBuilder& BodyBuilder::Position(Vector2 position)
    {
        m_bodyDef.position = position;
        return *this;
    }

    Body BodyBuilder::Build()
    {
        return m_engine.CreateBody(m_bodyDef);
    }
}
