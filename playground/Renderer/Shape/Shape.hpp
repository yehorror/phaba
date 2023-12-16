#pragma once

#include <span>
#include <glm/vec2.hpp>
#include <GL/glew.h>

namespace Playground
{
    class Shape
    {
    public:
        explicit Shape(const std::span<const glm::vec2> vertices);

    public:
        void Bind() const;
        void Draw() const;

    private:
        GLuint m_vertexArrayID;
        GLuint m_vertexBuffer;
        GLuint m_elementBuffer;
        const size_t m_elementsNum;
    };
}