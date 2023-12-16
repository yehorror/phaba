#include "Scene.hpp"
#include "Loader/Loader.hpp"

namespace Playground
{
    Scene::Scene()
    {
        static const Playground::Color s_whiteBox[] = {
            Playground::kWhite, Playground::kWhite, Playground::kWhite, Playground::kWhite
        };

        m_whiteColors = Playground::Colors(s_whiteBox);
    }

    void Scene::AddObject(const Object& object)
    {
        m_objects.emplace_back(object);
    }

    void Scene::Render(Renderer& renderer)
    {
        for (const auto& object : m_objects)
        {
            renderer.Draw(object.shape, m_whiteColors, object.angle, object.position);
        }
    }
}
