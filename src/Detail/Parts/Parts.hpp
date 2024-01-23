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

        BodyPart CreatePart(std::span<Vector2> vertices);

    private:
        GL::Buffer m_partsVertices{ GL_SHADER_STORAGE_BUFFER };
        GL::Buffer m_partsVerticesIndices{ GL_SHADER_STORAGE_BUFFER };
        GL::Buffer m_partsDescriptors{ GL_SHADER_STORAGE_BUFFER };

        unsigned int m_lastVertexIndex = 0;
    };
}