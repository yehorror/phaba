#pragma once

#include <span>
#include <Buffer/Buffer.hpp>
#include "Common.hpp"
#include "BodyPart/BodyPart.hpp"
#include "Descriptors/PartsDescriptors.hpp"
#include "Vertices/PartsVertices.hpp"

namespace Phaba::Detail
{
    class Parts
    {
    public:
        Parts();

        BodyPart CreatePart(std::span<const Vector2> vertices);

        PartDescriptor CreatePartDescriptor(std::span<VerticesIndices> partsIndices);

    private:
        PartsVertices m_vertices;
        PartsDescriptors m_partsDescriptors;
    };
}