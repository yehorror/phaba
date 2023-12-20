#pragma once

#include <GL/glew.h>

namespace GL
{
    class MappedMemoryGuard
    {
    public:
        MappedMemoryGuard(void* ptr, GLuint buffer);
        ~MappedMemoryGuard();

        void* get();
        operator void* ();

    private:
        void* m_ptr;
        const GLuint m_buffer;
    };

    class Buffer
    {
    public:
        explicit Buffer(GLenum bufferType);

        void bind() const;
        void bufferData(void* ptr, size_t size, GLenum type);
        void bindBase(unsigned int ID) const;

        void unbind() const;

        MappedMemoryGuard mapMemory(GLenum access) const;

        ~Buffer();

    private:
        GLuint m_buffer{};
        const GLenum m_bufferType;
    };
}