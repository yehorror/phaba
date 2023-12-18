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

    GLuint CreateBuffer(Bodies& bodies)
    {
        GLuint buffer{};
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(bodies), &bodies, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        return buffer;
    }
}

namespace Phaba
{
    World::World(Vector2 freeFallAcceleration)
        : m_freeFallAcceleration(std::move(freeFallAcceleration))
        , m_computeProgram(CreateComputeShader())
    {
        // Initialize world with 0 bodies
        Bodies bodies{};

        bodies.freeFallAcceleration = m_freeFallAcceleration;

        m_bodiesBuffer = CreateBuffer(bodies);
    }

    Body& World::CreateBody()
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bodiesBuffer);
        auto bodies = reinterpret_cast<Bodies*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE));

        const auto index = bodies->bodiesNum++;

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        return m_bodiesVec.emplace_back(*this, index);
    }

    Vector2 World::GetVelocity(unsigned int index) const
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bodiesBuffer);
        auto bodies = reinterpret_cast<Bodies*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY));

        const auto velocity = bodies->bodies[index].velocity;

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        return velocity;
    }

    void World::Step(TimeDelta timeDelta)
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bodiesBuffer);
        auto bodies = reinterpret_cast<Bodies*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY));
        bodies->timeDelta = timeDelta;

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        m_computeProgram.use();
        glDispatchCompute(1, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    }
}