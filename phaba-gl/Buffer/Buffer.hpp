#pragma once

#include <GL/glew.h>

namespace GL
{
    class Buffer
    {
    public:
        explicit Buffer(GLenum bufferType);

        void bind() const;
        void bufferData(void* ptr, size_t size, GLenum type);
        void bindBase(unsigned int ID) const;

        void unbind() const;

        ~Buffer();

    private:
        GLuint m_buffer{};
        const GLenum m_bufferType;
    };
}