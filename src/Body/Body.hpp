#pragma once

#include "Common.hpp"

namespace Phaba
{
    namespace Detail
    {
        class Engine;
    }

    enum class BodyType
    {
        kStatic = 0,
        kDynamic = 1
    };

    class Body
    {
    public:
        Body(Detail::Engine& engine, unsigned int index);

        Vector2 GetVelocity() const;
        Vector2 GetPosition() const;

    private:
        Detail::Engine& m_engine;
        const unsigned int m_index;
    };
}