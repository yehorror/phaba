#include "Colors.hpp"

namespace Playground
{
    Colors::Colors(const std::span<const Color>& colors)
    {
        glGenBuffers(1, &m_colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size_bytes(), colors.data(), GL_STATIC_DRAW);
    }

    Colors::Colors(Colors&& rhs) noexcept
        : m_colorBuffer(rhs.m_colorBuffer)
    {
        rhs.m_colorBuffer = 0;
    }

    Colors& Colors::operator=(Colors&& rhs) noexcept
    {
        m_colorBuffer = rhs.m_colorBuffer;
        rhs.m_colorBuffer = 0;

        return *this;
    }

    Colors::~Colors()
    {
        if (m_colorBuffer)
        {
            glDeleteBuffers(1, &m_colorBuffer);
        }
    }

    void Colors::Bind(GLuint attributeIndex) const
    {
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
        glVertexAttribPointer(
            attributeIndex,                   // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );
    }
}
