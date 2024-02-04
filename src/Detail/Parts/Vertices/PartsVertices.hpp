#pragma once

#include <span>
#include "Common.hpp"
#include "Buffer/Buffer.hpp"

namespace Phaba::Detail
{
    class PartsVertices
    {
    public:
        PartsVertices();

        VerticesIndices PutVertices(std::span<const Vector2> vertices);

        void Bind();

    private:
        GL::Buffer m_verticesBuffer{ GL_SHADER_STORAGE_BUFFER };

        unsigned int m_lastVertexIndex = 0;
    };
}