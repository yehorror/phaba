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

        void Render(Renderer& renderer);

    protected:
        
        void AddObject(const Object& object);

    private:

        virtual void OnRender() {}

        virtual void OnInput() {} // TODO

    private:
        Playground::Colors m_whiteColors;

        std::vector<Object> m_objects;

        float m_angle{ 0.0f };
    };
}