#pragma once

#include "Common.hpp"

namespace Phaba
{
    class Body
    {
    public:

        Vector2 GetVelocity() const;
        void SetVelocity(Vector2 velocity);

    private:
        Vector2 m_velocity;
    };
}