#pragma once

#include <vector>
#include "Renderer/Renderer.hpp"
#include "Object/Object.hpp"

namespace Playground
{
    class GenericScene
    {
    public:
        GenericScene();

        void AddObject(const Object& object);

        void Render(Renderer& renderer);

    private:
        Playground::Colors m_whiteColors;

        std::vector<Object> m_objects;

        float m_angle{ 0.0f };
    };
}