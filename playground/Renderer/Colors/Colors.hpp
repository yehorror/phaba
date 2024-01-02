#pragma once

#include <span>
#include "Buffer/Buffer.hpp"

namespace Playground
{
#pragma pack(push, 1)
    struct Color
    {
        float r;
        float g;
        float b;
    };
#pragma pack(pop)

    class Colors
    {
    public:
        explicit Colors(const std::span<const Color>& colors);

        Colors() = default;
        Colors(Colors&& rhs) = default;
        Colors& operator= (Colors&& rhs) = default;

        void Bind(GLuint attributeIndex) const;

    private:
        GL::Buffer m_buffer{ GL_ARRAY_BUFFER };
    };

    constexpr Playground::Color kWhite = { 1.f, 1.f, 1.f };
    constexpr Playground::Color kRed = { 1.f, 0.f, 0.f };
}