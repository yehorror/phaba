#pragma once

#include <span>
#include <GL/glew.h>

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

        void Bind(GLuint attributeIndex) const;

    private:
        GLuint m_colorBuffer;
    };

    constexpr Playground::Color kWhite = { 1.f, 1.f, 1.f };
    constexpr Playground::Color kRed = { 1.f, 0.f, 0.f };
}