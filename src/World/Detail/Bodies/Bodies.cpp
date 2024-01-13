#include "Bodies.hpp"

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
        auto bodies = reinterpret_cast<BodiesStruct*>(mappedMemory.get());

        const auto index = bodies->bodiesNum++;

        bodies->bodies[index].type = def.type;
        bodies->bodies[index].position = def.position;

        return Body(*this, index);
    }

    Vector2 Bodies::GetVelocity(unsigned int index)
    {
        auto mappedMemory = m_bodiesBuffer.mapMemory(GL_READ_ONLY);
        auto bodies = reinterpret_cast<BodiesStruct*>(mappedMemory.get());

        return bodies->bodies[index].velocity;
    }

    Vector2 Bodies::GetPosition(unsigned int index)
    {
        auto mappedMemory = m_bodiesBuffer.mapMemory(GL_READ_ONLY);
        auto bodies = reinterpret_cast<BodiesStruct*>(mappedMemory.get());

        return bodies->bodies[index].position;
    }

    void Bodies::Bind()
    {
        constexpr unsigned int kBodiesBufferBinding = 1;
        m_bodiesBuffer.bindBase(kBodiesBufferBinding);
    }
}