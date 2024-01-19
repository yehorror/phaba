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

    Body BodyBuilder::Build()
    {
        return m_engine.CreateBody(m_bodyDef);
    }
}
