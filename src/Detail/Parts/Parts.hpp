#pragma once

#include <span>
#include <Buffer/Buffer.hpp>
#include "Common.hpp"
#include "BodyPart/BodyPart.hpp"

namespace Phaba::Detail
{
    class Parts
    {
    public:
        Parts();

        BodyPart CreatePart(std::span<const Vector2> vertices);

    private:
        GL::Buffer m_partsVertices{ GL_SHADER_STORAGE_BUFFER }; // represents vertices of parts
        GL::Buffer m_partsVerticesIndices{ GL_SHADER_STORAGE_BUFFER }; // represents indices of vertices of parts
        GL::Buffer m_partsDescriptors{ GL_SHADER_STORAGE_BUFFER };  // represents indices of parts

        unsigned int m_lastVertexIndex = 0;
    };
}