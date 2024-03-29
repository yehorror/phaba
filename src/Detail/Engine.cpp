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
        float angle;
        uint type;
        uint partsDescriptor;
    };

    layout(std430, binding = 0) buffer WorldConfig
    {
        vec2 freeFallAcceleration;
        float timeDelta;
    };

    layout(std430, binding = 1) buffer Bodies
    {
        int bodiesNum;
        int pad;
        Body bodies[];
    };

    layout(std430, binding = 2) buffer Vertices
    {
        vec2 vertices[];
    };

    layout(std430, binding = 3) buffer PartsDescriptors
    {
        uint values[];
    };

    bool IsPointInsideOfShape(vec2 point, uint shapeIndex)
    {
        return false;
    }

    void main()
    {
        // I know it is not paralleled now
        // It will be done a bit later when I get at least MVP of this library features done
        for (int i = 0; i < bodiesNum; ++i)
        {
            if (bodies[i].type == kStaticBodyType)
            {
                continue;
            }

            vec2 originalVelocity = bodies[i].velocity;
            bodies[i].velocity += freeFallAcceleration * timeDelta;

            // If the speed is variable through the time, the formula is
            // dx = (v1 + v2) * dt / 2.f;
            bodies[i].position += (originalVelocity + bodies[i].velocity) * timeDelta / 2.f;
        }

        for (int i = 0; i < bodiesNum; ++i)
        {
            for (int j = 0; j < bodiesNum; ++j)
            {
                
            }
        }
    }
    )compute";

    struct WorldConfig
    {
        Phaba::Vector2 freeFallAcceleration;
        float timeDelta;
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
    {
        WorldConfig config{};
        config.freeFallAcceleration = freeFallAcceleration;
        m_worldConfig.bufferData(&config, sizeof(config), GL_DYNAMIC_DRAW);
    }

    Body Engine::CreateBody(const BodyDef& def)
    {
        return m_bodies.Create(def);
    }
    
    BodyPart Engine::CreateBodyPart(std::span<const Vector2> vertices)
    {
        return m_bodiesParts.CreatePart(vertices);
    }

    PartDescriptor Engine::CreatePartsDescriptor(std::span<VerticesIndices> partsVerticesIndices)
    {
        return m_bodiesParts.CreatePartDescriptor(partsVerticesIndices);
    }
   
    void Engine::Step(TimeDelta time)
    {
        {
            auto mappedMemory = m_worldConfig.mapMemory(GL_READ_WRITE);

            auto worldConfig = mappedMemory.get<WorldConfig>();

            worldConfig->timeDelta = time;
        }

        m_worldConfig.bindBase(0);
        m_bodies.Bind();
        m_computeProgram.use();

        glDispatchCompute(1, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    }
}