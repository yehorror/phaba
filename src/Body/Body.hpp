#pragma once

#include "Common.hpp"

namespace Phaba
{
    namespace Detail
    {
        class Bodies;
    }

    enum class BodyType
    {
        kStatic = 0,
        kDynamic = 1
    };

    struct BodyDef
    {
        Vector2 position{};
        float angle{};
        float density{};
        BodyType type = BodyType::kDynamic;
        Detail::PartDescriptor partDescriptor;
    };

    class Body
    {
    public:
        Body(Detail::Bodies& bodies, unsigned int index);

        Vector2 GetVelocity() const;
        Vector2 GetPosition() const;
        float GetAngle() const;

    private:
        Detail::Bodies& m_bodies;
        const unsigned int m_index;
    };
}