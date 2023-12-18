#pragma once

#include <string_view>
#include <GL/glew.h>

namespace GL
{
    class Shader
    {
    public:
        Shader(std::string_view shaderCode, GLenum shaderType);

        ~Shader();

        GLuint handle();

    private:
        GLuint m_shader;
    };
}