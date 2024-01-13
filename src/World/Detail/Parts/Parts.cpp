#include "Parts.hpp"

namespace
{
    // Currently during development these are not too important
    // Later it will be possible to extend buffers in runtime (though it may affect performance)
    constexpr auto kVerticesPreAllocate = 100;

    using namespace Phaba;

    struct PartsStruct
    {
        Vector2 vertices[kVerticesPreAllocate];
    };
}

namespace Phaba::Detail
{
    Parts::Parts()
    {
        PartsStruct parts{};
        m_partsBuffer.bufferData(&parts, sizeof(parts), GL_DYNAMIC_DRAW);
    }

    BodyPart Parts::CreatePart(std::span<Vector2> vertices)
    {
        auto mappedMemory = m_partsBuffer.mapMemory(GL_WRITE_ONLY);
        auto vertices = mappedMemory.get<Vector2>();

        const auto startIndex = m_lastIndex;

        for (const auto& vertex : vertices)
        {
            vertices[m_lastIndex] = vertex;
            ++m_lastIndex;
        }

        return BodyPart(*this, startIndex, m_lastIndex);
    }
}