#pragma once

#include "Body/Body.hpp"

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

        Body Build();

    private:
        Detail::Engine& m_engine;
        BodyDef m_bodyDef;
    };
}