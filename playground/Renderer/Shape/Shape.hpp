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

        Shape() = default;
        Shape(Shape&& rhs);
        Shape& operator= (Shape&& rhs) noexcept;

        ~Shape();

    public:
        void Bind(GLuint attributeIndex) const;
        void Draw() const;

    private:
        GLuint m_vertexArrayID{};
        GLuint m_vertexBuffer{};
        GLuint m_elementBuffer{};
        size_t m_elementsNum{};
    };
}