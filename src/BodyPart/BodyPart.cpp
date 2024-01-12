#include "BodyPart.hpp"
#include "World/Detail/Engine.hpp"

namespace Phaba
{
    BodyPart::BodyPart(Detail::Engine& engine, unsigned int startIndex, unsigned int endIndex)
        : m_engine(engine)
        , m_startIndex(startIndex)
        , m_endIndex(endIndex)
    {
    }
}
