#pragma once

#include <Buffer/Buffer.hpp>
#include "Common.hpp"
#include "Body/Body.hpp"

namespace Phaba::Detail
{
    class Bodies
    {
    public:
        Bodies();
        
        Body Create(const BodyDef& def);

        Vector2 GetVelocity(unsigned int index);
        Vector2 GetPosition(unsigned int index);
        float GetAngle(unsigned int index);

        void Bind();

    private:
        GL::Buffer m_bodiesBuffer{ GL_SHADER_STORAGE_BUFFER };
    };
}