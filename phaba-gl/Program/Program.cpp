#include "Program.hpp"

namespace GL
{
    Program::Program()
        : m_program(glCreateProgram())
    {
    }

    Program& Program::attach(const Shader& shader)
    {
        glAttachShader(m_program, shader.handle());
        return *this;
    }

    void Program::link()
    {
        glLinkProgram(m_program);
    }

    void Program::use()
    {
        glUseProgram(m_program);
    }

    Program::~Program()
    {
        if (m_program)
        {
            glDeleteProgram(m_program);
        }
    }
}
