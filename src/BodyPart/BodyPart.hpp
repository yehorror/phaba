#pragma once

#include "Common.hpp"

namespace Phaba
{
    namespace Detail
    {
        class Parts;
    }

    class BodyPart
    {
    public:
        BodyPart(Detail::Parts& parts, unsigned int startIndex, unsigned int endIndex);

        Detail::VerticesIndices GetVerticesIndices() const;

    private:
        Detail::Parts& m_parts;
        const unsigned int m_start;
        const unsigned int m_end;
    };
}