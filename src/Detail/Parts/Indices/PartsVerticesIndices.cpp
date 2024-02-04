#include "PartsVerticesIndices.hpp"

namespace
{
    constexpr size_t kIndicesPreAllocate = 100;

    struct Indices
    {
        unsigned int start;
        unsigned int end;
    };

    struct PartsIndicesStruct
    {
        Indices indices[kIndicesPreAllocate];
    };
}

namespace Phaba::Detail
{
    PartsVerticesIndices::PartsVerticesIndices()
    {
        PartsIndicesStruct partsIndices{};
        m_partsIndicesBuffer.bufferData(&partsIndices, sizeof(partsIndices), GL_DYNAMIC_DRAW);
    }

    unsigned int PartsVerticesIndices::PutIndices(unsigned int start, unsigned int end)
    {
        auto mappedMemory = m_partsIndicesBuffer.mapMemory(GL_WRITE_ONLY);
        auto indices = mappedMemory.get<Indices>();

        indices[m_lastIndex] = { start, end };

        return m_lastIndex++;
    }
}