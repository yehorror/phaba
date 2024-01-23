#pragma once

#include "Body/Body.hpp"
#include "BodyPart/BodyPart.hpp"

namespace Phaba
{
    namespace Detail
    {
        class Engine;
    }

    // Yeah that sounds cool 
    class BodyBuilder
    {
    public:
        explicit BodyBuilder(Detail::Engine& engine);

        BodyBuilder& Type(BodyType type);
        BodyBuilder& Position(Vector2 position);
        BodyBuilder& Angle(float angle);
        BodyBuilder& Part(BodyPart part);

        Body Build();

    private:
        Detail::Engine& m_engine;
        BodyDef m_bodyDef;
    };
}