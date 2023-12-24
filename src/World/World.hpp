#pragma once

#include <vector>
#include <GL/glew.h>
#include <Program/Program.hpp>
#include <Buffer/Buffer.hpp>
#include "Common.hpp"
#include "Body/Body.hpp"
#include "Detail/Engine.hpp"

namespace Phaba
{
    struct BodyDef
    {
        Vector2 position{};
        float angle{};
        float density{};
        BodyType type = BodyType::kDynamic;
    };

    class World
    {
    public:
        explicit World(Vector2 freeFallAcceleration = {});

        Body CreateBody(Phaba::BodyType type = Phaba::BodyType::kDynamic);

        void Step(TimeDelta timeDelta);

    private:
        Detail::Engine m_engine;
    };
}