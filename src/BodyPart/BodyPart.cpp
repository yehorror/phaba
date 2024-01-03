#include "BodyPart.hpp"
#include "World/Detail/Engine.hpp"

namespace Phaba
{
    BodyPart::BodyPart(Detail::Engine& engine, unsigned int index)
        : m_engine(engine)
        , m_index(index)
    {
    }
}
