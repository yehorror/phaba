#pragma once

#include <span>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <Buffer/Buffer.hpp>

namespace Playground
{
    class Shape
    {
    public:
        explicit Shape(const std::span<const glm::vec2> vertices);

        Shape() = default;
        Shape(Shape&& rhs);
        Shape& operator= (Shape&& rhs) noexcept;

        ~Shape();

    public:
        void Bind(GLuint attributeIndex) const;
        void Draw() const;

    private:
        GLuint m_vertexArrayID{};
        GL::Buffer m_vertexBuffer{GL_ARRAY_BUFFER};
        GL::Buffer m_elementBuffer{ GL_ELEMENT_ARRAY_BUFFER };
        size_t m_elementsNum{};
    };
}