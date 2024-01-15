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

        Body Build(const BodyDef& def);

    private:
        Detail::Engine& m_engine;
    };
}