#include "Parts.hpp"

namespace
{
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
        // TODO push vertices to  the buffer
        return BodyPart(*this, 0, 1);
    }
}