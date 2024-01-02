#include "GenericScene.hpp"

namespace Playground
{
    GenericScene::GenericScene()
    {
        static const Playground::Color s_whiteBox[] = {
            Playground::kWhite, Playground::kWhite, Playground::kWhite, Playground::kWhite
        };

        m_whiteColors = Playground::Colors(s_whiteBox);
    }

    void GenericScene::AddObject(const ObjectDef& object)
    {
        m_objects.emplace_back(
            Object
            {
                .physicalBody = m_world.CreateBody(
                    Phaba::BodyDef{
                        .position = object.position,
                        .angle = object.angle,
                        .type = object.type
                    }),
                .shape = object.shape,
                .position = object.position,
                .angle = object.angle
            });
    }

    void GenericScene::Step(float dt)
    {
        m_world.Step(dt);
        
        for (auto& object : m_objects)
        {
            object.position = object.physicalBody.GetPosition();
        }
    }

    void GenericScene::Render(Renderer& renderer)
    {
        for (const auto& object : m_objects)
        {
            renderer.Draw(object.shape, m_whiteColors, object.angle, object.position);
        }
    }
}
