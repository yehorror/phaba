#include "World.hpp"
#include <stdexcept>
#include <string_view>

namespace
{
    constexpr std::string_view kComputeShader = R"compute(
    #version 430 core

    layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

    struct Body
    {
        vec2 velocity;
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
            bodies[i].velocity += freeFallAcceleration * timeDelta;
        }
    }

    )compute";

    constexpr size_t kBodiesPreAllocate = 5;

    struct Body
    {
        Phaba::Vector2 velocity;
    };

    struct Bodies
    {
        int bodiesNum;
        float timeDelta;
        Phaba::Vector2 freeFallAcceleration;
        Body bodies[kBodiesPreAllocate];
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

namespace Phaba
{
    World::World(Vector2 freeFallAcceleration)
        : m_freeFallAcceleration(std::move(freeFallAcceleration))
        , m_computeProgram(CreateComputeShader())
        , m_bodiesBuffer(GL_SHADER_STORAGE_BUFFER)
    {
        // Initialize world with 0 bodies
        Bodies bodies{};

        bodies.freeFallAcceleration = m_freeFallAcceleration;

        m_bodiesBuffer.bind();
        m_bodiesBuffer.bufferData(&bodies, sizeof(bodies), GL_DYNAMIC_DRAW);
        m_bodiesBuffer.bindBase(0);

        m_bodiesBuffer.unbind();
    }

    Body& World::CreateBody()
    {
        auto mappedMemory = m_bodiesBuffer.mapMemory(GL_READ_WRITE);
        auto bodies = reinterpret_cast<Bodies*>(mappedMemory.get());

        const auto index = bodies->bodiesNum++;

        return m_bodiesVec.emplace_back(*this, index);
    }

    Vector2 World::GetVelocity(unsigned int index) const
    {
        auto mappedMemory = m_bodiesBuffer.mapMemory(GL_READ_WRITE);
        auto bodies = reinterpret_cast<Bodies*>(mappedMemory.get());

        const auto velocity = bodies->bodies[index].velocity;

        return velocity;
    }

    void World::Step(TimeDelta timeDelta)
    {
        {
            auto mappedMemory = m_bodiesBuffer.mapMemory(GL_WRITE_ONLY);

            auto bodies = reinterpret_cast<Bodies*>(mappedMemory.get());
            bodies->timeDelta = timeDelta;
        }

        m_computeProgram.use();

        glDispatchCompute(1, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    }
}