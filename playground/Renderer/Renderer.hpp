#pragma once

#include <GL/glew.h>

namespace Playground 
{
    class Renderer
    {
    public:
        Renderer();

        void Draw();

    private:
        GLuint m_vertexArrayID;
        GLuint m_vertexBuffer;
        GLuint m_elementBuffer;
        GLuint m_ubo;
        GLuint m_programID;
        GLuint m_uboID;
        GLuint m_colorBuffer;

        float m_scale;
    };
}