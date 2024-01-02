#pragma once

#include <vector>
#include "Renderer/Renderer.hpp"
#include "Object/Object.hpp"
#include "World/World.hpp"

namespace Playground
{
    struct ObjectDef
    {
        Playground::Shape& shape;
        glm::vec2 position;
        float density;
        float angle;
        Phaba::BodyType type;
    };

    class GenericScene
    {
    public:
        GenericScene();

        void Step(float dt);
        void Render(Renderer& renderer);

    protected:
        
        void AddObject(const ObjectDef& object);

    private:
        Playground::Colors m_whiteColors;

        std::vector<Object> m_objects;
        Phaba::World m_world{ {0.f, -9.8f} };
    };
}