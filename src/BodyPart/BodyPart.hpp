#pragma once

namespace Phaba
{
    namespace Detail
    {
        class Parts;
    }

    struct VerticesIndices
    {
        unsigned int start;
        unsigned int end;
    };

    class BodyPart
    {
    public:
        BodyPart(Detail::Parts& parts, unsigned int startIndex, unsigned int endIndex);

        VerticesIndices GetVerticesIndices() const;

    private:
        Detail::Parts& m_parts;
        const VerticesIndices m_verticesIndices;
    };
}