#pragma once

#include <GL/glew.h>

namespace GL
{
    class MappedMemoryGuard
    {
    public:
        MappedMemoryGuard(void* ptr, GLuint buffer);
        ~MappedMemoryGuard();

        operator void* ();

    public:
        template<typename StructType>
        StructType* get()
        {
            return static_cast<StructType*>(get());
        }

    private:
        void* get();

    private:
        void* m_ptr;
        const GLuint m_buffer;
    };

    class Buffer
    {
    public:
        explicit Buffer(GLenum bufferType);

        Buffer(Buffer&& rhs);
        Buffer& operator = (Buffer&& rhs);

        void bind() const;
        void bufferData(const void* ptr, size_t size, GLenum type);
        void bindBase(unsigned int ID) const;

        void unbind() const;

        MappedMemoryGuard mapMemory(GLenum access) const;

        ~Buffer();

    private:
        GLuint m_buffer{};
        GLenum m_bufferType;
    };
}