#include "BodyBuilder.hpp"
#include "Detail/Engine.hpp"

namespace Phaba
{
    BodyBuilder::BodyBuilder(Detail::Engine& engine)
        : m_engine(engine)
    {
    }

    BodyBuilder& BodyBuilder::Type(BodyType type)
    {
        m_bodyDef.type = type;
        return *this;
    }

    BodyBuilder& BodyBuilder::Position(Vector2 position)
    {
        m_bodyDef.position = position;
        return *this;
    }
    BodyBuilder& BodyBuilder::Angle(float angle)
    {
        m_bodyDef.angle = angle;
        return *this;
    }

    BodyBuilder& BodyBuilder::Part(const BodyPart& part)
    {
        m_partsIndices.push_back(part.GetVerticesIndices());
        return *this;
    }

    Body BodyBuilder::Build()
    {
        m_bodyDef.partDescriptor = m_engine.CreatePartsDescriptor(m_partsIndices);
        return m_engine.CreateBody(m_bodyDef);
    }
}
