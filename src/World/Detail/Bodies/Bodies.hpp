#pragma once

#include <Buffer/Buffer.hpp>
#include "Common.hpp"
#include "Body/Body.hpp"

namespace Phaba::Detail
{
    constexpr size_t kBodiesPreAllocate = 5;

    struct BodyStruct
    {
        Phaba::Vector2 position;
        Phaba::Vector2 velocity;
        Phaba::BodyType type;
    };

    struct BodiesStruct
    {
        int bodiesNum;
        int pad;
        BodyStruct bodies[kBodiesPreAllocate];
    };

    class Bodies
    {
    public:
        GL::Buffer m_bodiesBuffer{ GL_SHADER_STORAGE_BUFFER };

    private:

    };
}