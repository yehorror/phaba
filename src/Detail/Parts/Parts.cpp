#include "Parts.hpp"

namespace Phaba::Detail
{
    Parts::Parts()
    {
    }

    BodyPart Parts::CreatePart(std::span<const Vector2> vertices)
    {
        auto verticesIndices = m_vertices.PutVertices(vertices);
    }
}