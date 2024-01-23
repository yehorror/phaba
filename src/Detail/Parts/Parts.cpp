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
        m_partsVertices.bufferData(&parts, sizeof(parts), GL_DYNAMIC_DRAW);
    }

    BodyPart Parts::CreatePart(std::span<const Vector2> vertices)
    {
        // TODO memcpy?
        auto mappedMemory = m_partsVertices.mapMemory(GL_WRITE_ONLY);
        auto verticesMemory = mappedMemory.get<Vector2>();

        const auto startIndex = m_lastVertexIndex;

        for (const auto& vertex : vertices)
        {
            verticesMemory[m_lastVertexIndex] = vertex;
            ++m_lastVertexIndex;
        }

        return BodyPart(*this, startIndex, m_lastVertexIndex);
    }
}