#pragma once

#include "Common.hpp"

namespace Phaba
{
    class World;

    class Body
    {
    public:
        Body(World& world, unsigned int index);

        Vector2 GetVelocity() const;
        void SetVelocity(Vector2 velocity);

    private:
        World& m_world;
        const unsigned int m_index;
    };
}