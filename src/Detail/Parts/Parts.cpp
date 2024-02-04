#include "Parts.hpp"

namespace Phaba::Detail
{
    Parts::Parts()
    {
    }

    BodyPart Parts::CreatePart(std::span<const Vector2> vertices)
    {
        const auto [start, end] = m_vertices.PutVertices(vertices);
        return BodyPart(*this, start, end);
    }

    PartDescriptor Parts::CreatePartDescriptor(std::span<unsigned int> partsIndices)
    {
        return m_partsDescriptors.MakePartDescriptor(partsIndices);
    }
}