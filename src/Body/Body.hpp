#pragma once

#include "Common.hpp"

namespace Phaba
{
    class World;

    enum class BodyType
    {
        kStatic = 0,
        kDynamic = 1
    };

    class Body
    {
    public:
        Body(World& world, unsigned int index);

        Vector2 GetVelocity() const;
        Vector2 GetPosition() const;

    private:
        World& m_world;
        const unsigned int m_index;
    };
}