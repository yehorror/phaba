#include "BodyPart.hpp"
#include "Detail/Parts/Parts.hpp"

namespace Phaba
{
    BodyPart::BodyPart(Detail::Parts& parts, unsigned int startIndex, unsigned int endIndex)
        : m_parts(parts)
        , m_start(startIndex)
        , m_end(endIndex)
    {
    }

    Detail::VerticesIndices BodyPart::GetVerticesIndices() const
    {
        return { m_start, m_end };
    }
}
