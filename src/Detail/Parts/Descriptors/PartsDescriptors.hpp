#pragma once

#include <span>
#include "Common.hpp"
#include "Buffer/Buffer.hpp"

namespace Phaba::Detail
{
    using PartDescriptor = unsigned int;

    class PartsDescriptors
    {
    public:
        PartsDescriptors();

        PartDescriptor MakePartDescriptor(std::span<VerticesIndices> partsIndices);

    private:
        GL::Buffer m_partDescriptors{ GL_SHADER_STORAGE_BUFFER };

        unsigned int m_lastFreeElementIndex = 0;
    };
}