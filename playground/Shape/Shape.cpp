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

        m_vertexBuffer.bufferData(vertices.data(), vertices.size_bytes(), GL_STATIC_DRAW);

        const auto indices = GenerateIndices(vertices.size());

        glGenBuffers(1, &m_elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    Shape::Shape(Shape&& rhs)
        : m_vertexArrayID(rhs.m_vertexArrayID)
        , m_vertexBuffer(std::move(rhs.m_vertexBuffer))
        , m_elementBuffer(rhs.m_elementBuffer)
        , m_elementsNum(rhs.m_elementsNum)
    {
        rhs.m_vertexArrayID = 0;
        rhs.m_elementBuffer = 0;
        rhs.m_elementsNum = 0;
    }

    Shape& Shape::operator=(Shape&& rhs) noexcept
    {
        m_vertexArrayID = rhs.m_vertexArrayID;
        m_vertexBuffer = std::move(rhs.m_vertexBuffer);
        m_elementBuffer = rhs.m_elementBuffer;
        m_elementsNum = rhs.m_elementsNum;

        rhs.m_vertexArrayID = 0;
        rhs.m_elementBuffer = 0;
        rhs.m_elementsNum = 0;

        return *this;
    }

    Shape::~Shape()
    {
        if (m_vertexArrayID)
        {
            glDeleteVertexArrays(1, &m_vertexArrayID);
        }

        if (m_elementBuffer)
        {
            glDeleteBuffers(1, &m_elementBuffer);
        }
    }

    void Shape::Bind(GLuint attributeIndex) const
    {
        glEnableVertexAttribArray(attributeIndex);

        m_vertexBuffer.bind();
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