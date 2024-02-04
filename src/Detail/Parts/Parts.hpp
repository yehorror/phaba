#pragma once

#include <span>
#include <Buffer/Buffer.hpp>
#include "Common.hpp"
#include "BodyPart/BodyPart.hpp"
#include "Descriptors/PartsDescriptors.hpp"
#include "Vertices/PartsVertices.hpp"
#include "Indices/PartsVerticesIndices.hpp"

namespace Phaba::Detail
{
    class Parts
    {
    public:
        Parts();

        BodyPart CreatePart(std::span<const Vector2> vertices);

        PartDescriptor CreatePartDescriptor(std::span<unsigned int> partsIndices);

    private:
        PartsVertices m_vertices;
        PartsVerticesIndices m_partsVerticesIndices;
        PartsDescriptors m_partsDescriptors;
    };
}