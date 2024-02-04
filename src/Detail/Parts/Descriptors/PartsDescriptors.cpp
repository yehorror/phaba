#include "PartsDescriptors.hpp"

namespace
{
    constexpr size_t kDescriptorsDataPreAllocate = 100;

    // LV structure (just like TLV, but without a 'Tag')
    struct DescriptorsStruct
    {
        int value[kDescriptorsDataPreAllocate];
    };
}

namespace Phaba::Detail
{
    PartsDescriptors::PartsDescriptors()
    {
        DescriptorsStruct descriptors{};
        m_partDescriptors.bufferData(&descriptors, sizeof(descriptors), GL_DYNAMIC_DRAW);
    }

    PartDescriptor PartsDescriptors::MakePartDescriptor(std::span<VerticesIndices> partsIndices)
    {
        auto mappedMemory = m_partDescriptors.mapMemory(GL_WRITE_ONLY);
        auto descriptors = mappedMemory.get<DescriptorsStruct>();

        auto descriptor = m_lastFreeElementIndex;

        descriptors->value[m_lastFreeElementIndex] = partsIndices.size();

        ++m_lastFreeElementIndex;

        for (const auto partIndex : partsIndices)
        {
            descriptors->value[m_lastFreeElementIndex] = partIndex.start;
            ++m_lastFreeElementIndex;

            descriptors->value[m_lastFreeElementIndex] = partIndex.end;
            ++m_lastFreeElementIndex;
        }

        return descriptor;
    }

    void PartsDescriptors::Bind()
    {
        constexpr unsigned int kPartsDescriptorsBinding = 3;
        m_partDescriptors.bindBase(kPartsDescriptorsBinding);
    }
}