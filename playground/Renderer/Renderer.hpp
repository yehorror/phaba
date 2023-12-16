#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "Shape/Shape.hpp"
#include "Colors/Colors.hpp"

namespace Playground
{
    class Renderer
    {
    public:
        Renderer();

        void Draw(const Shape& shape, const Colors& colors, float angle, glm::vec2 pos);

        void SetScale(float scale);

    private:
        struct UBO
        {
            glm::mat4x4 transform;
            glm::vec2 offset;
            float scale;
        };

    private:
        GLuint m_ubo;
        GLuint m_programID;
        GLuint m_uboID;
        
        float m_scale{ 1.f };
    };
}