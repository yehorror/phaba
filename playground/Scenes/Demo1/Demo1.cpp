#include "Demo1.hpp"

namespace
{
    const glm::vec2 g_boxVertices[]
    {
        {-1.0,  1.0},
        { 1.0,  1.0},
        { 1.0, -1.0},
        {-1.0, -1.0}
    };

    const glm::vec2 g_floorVertices[]
    {
        { -20.0,   0.1},
        {  20.0,   0.1},
        {  20.0,  -0.1},
        { -20.0,  -0.1}
    };
}

namespace Playground
{
    Demo1::Demo1()
        : m_boxShape(g_boxVertices)
        , m_floorShape(g_floorVertices)
    {
        AddObject({ .shape = m_boxShape, .position = {0.f, 5.f}, .angle = 0.f });
        AddObject({ .shape = m_floorShape, .position = {0.f, -5.f}, .angle = 0.f });
    }

    void Demo1::OnRender()
    {
    }
}
