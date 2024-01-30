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

        // PartDescriptor CreatePartDescriptor();

    private:
        PartsVertices m_vertices;
        GL::Buffer m_partsVerticesIndices{ GL_SHADER_STORAGE_BUFFER }; // represents indices of vertices of parts
        GL::Buffer m_partsDescriptors{ GL_SHADER_STORAGE_BUFFER };  // represents indices of parts
    };
}