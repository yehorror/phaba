#include "Scene.hpp"
#include "Loader/Loader.hpp"

namespace Playground
{
    Scene::Scene(Renderer& renderer)
        : m_renderer(renderer)
    {
        static const Playground::Color s_whiteBox[] = {
            Playground::kWhite, Playground::kWhite, Playground::kWhite, Playground::kWhite
        };

        m_whiteColors = std::move(Playground::Colors(std::span<const Playground::Color>(s_whiteBox)));

        auto boxVertices = Playground::LoadVertices("Misc/shapes/box");

        m_box = Playground::Shape(std::span<const glm::vec2>(boxVertices));
    }

    void Scene::Render()
    {
        m_angle += 0.001f;
        m_renderer.Draw(m_box, m_whiteColors, m_angle, { 0.5f, 0.5f });
        m_renderer.Draw(m_box, m_whiteColors, -m_angle, { -0.5f, -0.5f });
    }
}
