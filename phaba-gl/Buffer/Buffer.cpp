#include "Buffer.hpp"

namespace GL
{
    MappedMemoryGuard::MappedMemoryGuard(void* ptr, GLuint buffer)
        : m_ptr(ptr)
        , m_buffer(buffer)
    {
    }

    MappedMemoryGuard::~MappedMemoryGuard()
    {
        if (m_ptr && m_buffer)
        {
            glUnmapNamedBuffer(m_buffer);
        }
    }

    void* MappedMemoryGuard::get()
    {
        return m_ptr;
    }

    MappedMemoryGuard::operator void* ()
    {
        return m_ptr;
    }

    Buffer::Buffer(GLenum bufferType)
        : m_bufferType(bufferType)
    {
        glCreateBuffers(1, &m_buffer);
        bind();
        unbind();
    }

    void Buffer::bind() const
    {
        glBindBuffer(m_bufferType, m_buffer);
    }

    void Buffer::bufferData(void* ptr, size_t size, GLenum type)
    {
        glNamedBufferData(m_buffer, size, ptr, type);
    }

    void Buffer::bindBase(unsigned int ID) const
    {
        glBindBufferBase(m_bufferType, ID, m_buffer);
    }

    void Buffer::unbind() const
    {
        glBindBuffer(m_bufferType, 0);
    }

    MappedMemoryGuard Buffer::mapMemory(GLenum access) const
    {
        return MappedMemoryGuard(glMapNamedBuffer(m_buffer, access), m_buffer);
    }

    Buffer::~Buffer()
    {
        if (m_buffer)
        {
            glDeleteBuffers(1, &m_buffer);
        }
    }
}