#include "Bodies.hpp"

namespace
{
    constexpr size_t kBodiesPreAllocate = 5;

    // Legal in .cpp :p
    using namespace Phaba;

    struct BodyStruct
    {
        Vector2 position;
        Vector2 velocity;
        float angle;
        BodyType type;
        Detail::PartDescriptor partDescriptor;
    };

    struct BodiesStruct
    {
        int bodiesNum;
        int pad;
        BodyStruct bodies[kBodiesPreAllocate];
    };
}

namespace Phaba::Detail
{
    Bodies::Bodies()
    {
        // Initialize world with 0 bodies
        BodiesStruct bodies{};
        m_bodiesBuffer.bufferData(&bodies, sizeof(bodies), GL_DYNAMIC_DRAW);
    }

    Body Bodies::Create(const BodyDef& def)
    {
        auto mappedMemory = m_bodiesBuffer.mapMemory(GL_READ_WRITE);
        auto bodies = mappedMemory.get<BodiesStruct>();

        const auto index = bodies->bodiesNum++;

        bodies->bodies[index].type = def.type;
        bodies->bodies[index].position = def.position;
        bodies->bodies[index].angle = def.angle;
        bodies->bodies[index].partDescriptor = def.partDescriptor;

        return Body(*this, index);
    }

    Vector2 Bodies::GetVelocity(unsigned int index)
    {
        auto mappedMemory = m_bodiesBuffer.mapMemory(GL_READ_ONLY);
        auto bodies = mappedMemory.get<BodiesStruct>();

        return bodies->bodies[index].velocity;
    }

    Vector2 Bodies::GetPosition(unsigned int index)
    {
        auto mappedMemory = m_bodiesBuffer.mapMemory(GL_READ_ONLY);
        auto bodies = mappedMemory.get<BodiesStruct>();

        return bodies->bodies[index].position;
    }

    float Bodies::GetAngle(unsigned int index)
    {
        auto mappedMemory = m_bodiesBuffer.mapMemory(GL_READ_ONLY);
        auto bodies = mappedMemory.get<BodiesStruct>();

        return bodies->bodies[index].angle;
    }

    void Bodies::Bind()
    {
        constexpr unsigned int kBodiesBufferBinding = 1;
        m_bodiesBuffer.bindBase(kBodiesBufferBinding);
    }
}