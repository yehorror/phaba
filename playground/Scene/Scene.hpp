#pragma once

#include <vector>
#include "Renderer/Renderer.hpp"

namespace Playground
{
    class Scene
    {
    public:

        explicit Scene(Renderer& renderer);

        void Render();

    private:
        Renderer& m_renderer;
        Playground::Shape m_box;
        Playground::Colors m_whiteColors;

        float m_angle{ 0.0f };
    };
}