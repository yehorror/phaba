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
        static const GLfloat s_colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
        };

        glGenBuffers(1, &m_colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(s_colors), s_colors, GL_STATIC_DRAW);

        static const GLuint s_indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        glGenBuffers(1, &m_elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_indices), s_indices, GL_STATIC_DRAW);

        m_programID = LoadShaders();

        glUseProgram(m_programID);

        glGenBuffers(1, &m_ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

        m_uboID = glGetUniformBlockIndex(m_programID, "Matrices");
        glUniformBlockBinding(m_programID, m_uboID, 0);
    }

    void Renderer::Draw(const Shape& shape, float angle, glm::vec2 pos)
    {
        glEnableVertexAttribArray(0);

        shape.Bind();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);

        glVertexAttribPointer(
            0,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            nullptr
        );

        UBO uboData{};

        uboData.transform = glm::mat4x4{ 1.f };
        uboData.transform = glm::rotate(uboData.transform, angle, { 0.f, 0.f, 1.f });
        uboData.offset = pos;

        glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(uboData), &uboData, GL_STREAM_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_ubo, 0, sizeof(uboData));

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        shape.Draw();

        glDisableVertexAttribArray(0);
    }
}
