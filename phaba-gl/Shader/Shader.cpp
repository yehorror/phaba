#include "Shader.hpp"
#include <string>
#include <stdexcept>
#include <vector>

namespace GL
{
    Shader::Shader(std::string_view shaderCode, GLenum shaderType)
        : m_shader(glCreateShader(shaderType))
    {
        const char* shaderCodePtr = shaderCode.data();

        glShaderSource(m_shader, 1, &shaderCodePtr, nullptr);

        glCompileShader(m_shader);

        GLint param = GL_FALSE;
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &param);

        if (param != GL_TRUE)
        {
            GLint length{};
            glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &length);

            std::vector<char> errorMessage(length + 1);
            glGetShaderInfoLog(m_shader, length, NULL, errorMessage.data());
            throw std::runtime_error(
                "Failed to compile compute shader: " + std::string(errorMessage.cbegin(), errorMessage.cend())
            );
        }
    }

    Shader::~Shader()
    {
        if (m_shader)
        {
            glDeleteShader(m_shader);
        }
    }

    GLuint Shader::handle() const
    {
        return m_shader;
    }
}