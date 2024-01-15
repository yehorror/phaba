#include "BodyBuilder.hpp"
#include "World/Detail/Engine.hpp"

namespace Phaba
{
    BodyBuilder::BodyBuilder(Detail::Engine& engine)
        : m_engine(engine)
    {
    }

    Body BodyBuilder::Build(const BodyDef& def)
    {
        return m_engine.CreateBody(def);
    }
}
