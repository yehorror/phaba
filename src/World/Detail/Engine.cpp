#include "Engine.hpp"
#include "Body/Body.hpp"

namespace
{
    constexpr std::string_view kComputeShader = R"compute(
    #version 430 core

    layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

    const uint kStaticBodyType = 0x0;
    const uint kDynamicBodyType = 0x1;

    struct Body
    {
        vec2 position;
        vec2 velocity;
        uint type;
    };

    layout(std430, binding = 0) buffer Bodies
    {
        int bodiesNum;
        float timeDelta;
        vec2 freeFallAcceleration;
        Body bodies[];
    };

    void main()
    {
        for (int i = 0; i < bodiesNum; ++i)
        {
            if (bodies[i].type == kStaticBodyType)
            {
                continue;
            }

            vec2 originalVelocity = bodies[i].velocity;
            bodies[i].velocity += freeFallAcceleration * timeDelta;

            // If the speed is variable through the time, the formula is
            // dx = (v1 + v2) * dt / 2;
            bodies[i].position += (originalVelocity + bodies[i].velocity) * timeDelta / 2.f;
        }
    }

    )compute";

    constexpr size_t kBodiesPreAllocate = 5;

    struct BodyStruct
    {
        Phaba::Vector2 position;
        Phaba::Vector2 velocity;
        Phaba::BodyType type;
    };

    struct BodiesStruct
    {
        int bodiesNum;
        float timeDelta;
        Phaba::Vector2 freeFallAcceleration;
        BodyStruct bodies[kBodiesPreAllocate];
    };

    GL::Program CreateComputeShader()
    {
        GL::Program program;

        program
            .attach(GL::Shader(kComputeShader, GL_COMPUTE_SHADER))
            .link();

        return program;
    }
}

namespace Phaba::Detail
{
    Engine::Engine(Vector2 freeFallAcceleration)
        : m_computeProgram(CreateComputeShader())
        , m_bodiesParts(GL_SHADER_STORAGE_BUFFER)
    {
        // Initialize world with 0 bodies
        BodiesStruct bodies{};

        bodies.freeFallAcceleration = freeFallAcceleration;

        m_bodies.m_bodiesBuffer.bufferData(&bodies, sizeof(bodies), GL_DYNAMIC_DRAW);
        m_bodies.m_bodiesBuffer.bindBase(0);
    }

    Body Engine::CreateBody(const BodyDef& def)
    {
        auto mappedMemory = m_bodies.m_bodiesBuffer.mapMemory(GL_READ_WRITE);
        auto bodies = reinterpret_cast<BodiesStruct*>(mappedMemory.get());

        const auto index = bodies->bodiesNum++;

        bodies->bodies[index].type = def.type;
        bodies->bodies[index].position = def.position;

        return Body(*this, index);
    }
    /*
    BodyPart Engine::CreateBodyPart(std::span<Vector2> vertices)
    {
        return BodyPart(*this, );
    }
    */

    Vector2 Engine::GetVelocity(unsigned int index) const
    {
        auto mappedMemory = m_bodies.m_bodiesBuffer.mapMemory(GL_READ_ONLY);
        auto bodies = reinterpret_cast<BodiesStruct*>(mappedMemory.get());

        return bodies->bodies[index].velocity;
    }

    Vector2 Engine::GetPosition(unsigned int index) const
    {
        auto mappedMemory = m_bodies.m_bodiesBuffer.mapMemory(GL_READ_ONLY);
        auto bodies = reinterpret_cast<BodiesStruct*>(mappedMemory.get());

        return bodies->bodies[index].position;
    }

    void Engine::Step(TimeDelta time)
    {
        {
            auto mappedMemory = m_bodies.m_bodiesBuffer.mapMemory(GL_WRITE_ONLY);

            auto bodies = reinterpret_cast<BodiesStruct*>(mappedMemory.get());
            bodies->timeDelta = time;
        }

        m_bodies.m_bodiesBuffer.bind();
        m_computeProgram.use();

        glDispatchCompute(1, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        m_bodies.m_bodiesBuffer.unbind();
    }
}