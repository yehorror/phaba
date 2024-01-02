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

        m_elementBuffer.bufferData(indices.data(), indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
    }

    Shape::Shape(Shape&& rhs) noexcept
        : m_vertexArrayID(rhs.m_vertexArrayID)
        , m_vertexBuffer(std::move(rhs.m_vertexBuffer))
        , m_elementBuffer(std::move(rhs.m_elementBuffer))
        , m_elementsNum(rhs.m_elementsNum)
    {
        rhs.m_vertexArrayID = 0;
        rhs.m_elementsNum = 0;
    }

    Shape& Shape::operator=(Shape&& rhs) noexcept
    {
        m_vertexArrayID = rhs.m_vertexArrayID;
        m_vertexBuffer = std::move(rhs.m_vertexBuffer);
        m_elementBuffer = std::move(rhs.m_elementBuffer);
        m_elementsNum = rhs.m_elementsNum;

        rhs.m_vertexArrayID = 0;
        rhs.m_elementsNum = 0;

        return *this;
    }

    Shape::~Shape()
    {
        if (m_vertexArrayID)
        {
            glDeleteVertexArrays(1, &m_vertexArrayID);
        }
    }

    void Shape::Bind(GLuint attributeIndex) const
    {
        glEnableVertexAttribArray(attributeIndex);
        glBindVertexArray(m_vertexArrayID);

        m_vertexBuffer.bind();
        m_elementBuffer.bind();

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

    std::vector<glm::vec2> Shape::GetVertices() const
    {
        auto memory = m_vertexBuffer.mapMemory(GL_READ_ONLY);

        auto begin = reinterpret_cast<glm::vec2*>(memory.get());
        auto end = begin + (m_elementsNum / 3 + 2);

        return std::vector<glm::vec2>(begin, end);
    }
}