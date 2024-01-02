#include "Colors.hpp"

namespace Playground
{
    Colors::Colors(const std::span<const Color>& colors)
    {
        m_buffer.bufferData(colors.data(), colors.size_bytes(), GL_STATIC_DRAW);
    }

    void Colors::Bind(GLuint attributeIndex) const
    {
        glEnableVertexAttribArray(1);
        m_buffer.bind();
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
