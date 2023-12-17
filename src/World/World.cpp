#include "World.hpp"
#include <stdexcept>
#include <string_view>

namespace
{
    const char* kComputeShader = R"compute(
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
}

namespace Phaba
{
    World::World(Vector2 freeFallAcceleration)
        : m_freeFallAcceleration(std::move(freeFallAcceleration))
        , m_computeProgram(glCreateProgram())
    {
        const auto computeShader = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(computeShader, 1, &kComputeShader, nullptr);
        glCompileShader(computeShader);

        GLint param = GL_FALSE;
        glGetShaderiv(computeShader, GL_COMPILE_STATUS, &param);

        if (param != GL_TRUE)
        {
            GLint length{};
            glGetShaderiv(computeShader, GL_INFO_LOG_LENGTH, &length);

            std::vector<char> VertexShaderErrorMessage(length + 1);
            glGetShaderInfoLog(computeShader, length, NULL, &VertexShaderErrorMessage[0]);
            throw std::runtime_error(
                "Failed to compile compute shader: " + std::string(VertexShaderErrorMessage.cbegin(), VertexShaderErrorMessage.cend())
            );
        }

        glAttachShader(m_computeProgram, computeShader);
        glLinkProgram(m_computeProgram);

        // Initialize world with 0 bodies
        Bodies bodies{};

        bodies.freeFallAcceleration = m_freeFallAcceleration;

        glGenBuffers(1, &m_bodies);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bodies);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(bodies), &bodies, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_bodies);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    Body& World::CreateBody()
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bodies);
        auto bodies = reinterpret_cast<Bodies*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE));

        const auto index = bodies->bodiesNum++;

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        return m_bodiesVec.emplace_back(*this, index);
    }

    Vector2 World::GetVelocity(unsigned int index) const
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bodies);
        auto bodies = reinterpret_cast<Bodies*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY));

        const auto velocity = bodies->bodies[index].velocity;

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        return velocity;
    }

    void World::Step(TimeDelta timeDelta)
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bodies);
        auto bodies = reinterpret_cast<Bodies*>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY));
        bodies->timeDelta = timeDelta;

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        glUseProgram(m_computeProgram);
        glDispatchCompute(1, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        /*
        for (auto& body : m_bodiesVec)
        {
            body.SetVelocity(body.GetVelocity() + m_freeFallAcceleration * timeDelta);
        }
        */
    }
}