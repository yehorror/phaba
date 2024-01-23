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
        GL::Buffer m_partsBuffer{ GL_SHADER_STORAGE_BUFFER };
        unsigned int m_lastIndex = 0;
    };
}