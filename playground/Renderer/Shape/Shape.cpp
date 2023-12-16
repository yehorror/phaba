#include <vector>
#include "Shape.hpp"

namespace
{
    std::vector<GLuint> GenerateIndices(unsigned int size)
    {
        std::vector<GLuint> result;

        const size_t numTriangles = size - 2;

        result.reserve(numTriangles * 3);

        GLuint current = 1;
        for (size_t i = 0; i < numTriangles; ++i)
        {
            // Looks weird, but that's how indices are generated
            // Always use first vertex, second vertex is last from previous element
            // And the last one is the next vertex
            result.push_back(0);
            result.push_back(current);
            result.push_back(++current);
        }
        
        return result;
    }
}

namespace Playground
{
    Shape::Shape(const std::span<const glm::vec2> vertices)
        : m_elementsNum((vertices.size() - 2) * 3)
    {
        glGenVertexArrays(1, &m_vertexArrayID);
        glBindVertexArray(m_vertexArrayID);

        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

        glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);

        const auto indices = GenerateIndices(vertices.size());

        glGenBuffers(1, &m_elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    void Shape::Bind(GLuint attributeIndex) const
    {
        glEnableVertexAttribArray(attributeIndex);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);

        glVertexAttribPointer(
            attributeIndex,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            nullptr
        );

    }

    void Shape::Draw() const
    {
        glDrawElements(
            GL_TRIANGLES,       // mode
            m_elementsNum,      // count
            GL_UNSIGNED_INT,    // type
            (void*)0            // element array buffer offset
        );
    }
}