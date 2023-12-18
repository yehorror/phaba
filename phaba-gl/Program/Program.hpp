#pragma once

#include "Shader/Shader.hpp"

namespace GL
{
    class Program
    {
    public:
        Program();

        Program& attach(const Shader& shader);
        void link();

        void use();

        ~Program();

    private:
        GLuint m_program;
    };
}