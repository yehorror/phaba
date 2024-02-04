#pragma once

#include "Buffer/Buffer.hpp"

namespace Phaba::Detail
{
    class PartsVerticesIndices
    {
    public:
        PartsVerticesIndices();

        unsigned int PutIndices(unsigned int start, unsigned int end);

    private:
        GL::Buffer m_partsIndicesBuffer{ GL_SHADER_STORAGE_BUFFER };
        unsigned int m_lastIndex = 0;
    };
}