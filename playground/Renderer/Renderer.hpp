#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "Shape/Shape.hpp"

namespace Playground
{
    class Renderer
    {
    public:
        Renderer();

        void Draw(const Shape& shape, float angle, glm::vec2 pos);

    private:
        struct UBO
        {
            glm::mat4x4 transform;
            glm::vec2 offset;
        };

    private:
        GLuint m_elementBuffer;
        GLuint m_ubo;
        GLuint m_programID;
        GLuint m_uboID;
        GLuint m_colorBuffer;
    };
}