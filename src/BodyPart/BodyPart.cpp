#include "BodyPart.hpp"
#include "World/Detail/Parts/Parts.hpp"

namespace Phaba
{
    BodyPart::BodyPart(Detail::Parts& parts, unsigned int startIndex, unsigned int endIndex)
        : m_parts(parts)
        , m_startIndex(startIndex)
        , m_endIndex(endIndex)
    {
    }
}
