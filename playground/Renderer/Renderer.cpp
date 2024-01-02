#include "Renderer.hpp"
#include "Shaders/Shaders.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

namespace
{
    GLuint LoadShaders()
    {
        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        std::string VertexShaderCode = VERTEX_SHADER.data();
        std::string FragmentShaderCode = FRAGMENT_SHADER.data();
        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Compile Vertex Shader
        char const* VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }

        // Compile Fragment Shader
        char const* FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }

        // Link the program
        printf("Linking program\n");
        GLuint ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);

        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }

        glDetachShader(ProgramID, VertexShaderID);
        glDetachShader(ProgramID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        return ProgramID;
    }
}

namespace Playground
{
    Renderer::Renderer()
    {
        m_programID = LoadShaders();

        glUseProgram(m_programID);

        glGenBuffers(1, &m_ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

        m_uboID = glGetUniformBlockIndex(m_programID, "Matrices");
        glUniformBlockBinding(m_programID, m_uboID, 0);
    }

    void Renderer::Draw(const Shape& shape, const Colors& colors, float angle, glm::vec2 pos)
    {
        glUseProgram(m_programID);

        shape.Bind(0);

        UBO uboData{};

        uboData.transform = glm::mat4x4{ 1.f };
        uboData.transform = glm::rotate(uboData.transform, angle, { 0.f, 0.f, 1.f });
        uboData.offset = pos;
        uboData.scale = m_scale;

        glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(uboData), &uboData, GL_STREAM_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_ubo, 0, sizeof(uboData));

        colors.Bind(1);
        shape.Draw();
    }

    void Renderer::SetScale(float scale)
    {
        m_scale = scale;
    }
}
