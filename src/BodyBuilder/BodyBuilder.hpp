#pragma once

#include <vector>
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
        BodyBuilder& Part(const BodyPart& part);

        Body Build();

    private:
        BodyDef m_bodyDef;
        std::vector<Detail::VerticesIndices> m_partsIndices;
        Detail::Engine& m_engine;
    };
}