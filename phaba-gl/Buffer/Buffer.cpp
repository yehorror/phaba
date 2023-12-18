#include "Buffer.hpp"

namespace GL
{
    Buffer::Buffer(GLenum bufferType)
        : m_bufferType(bufferType)
    {
        glGenBuffers(1, &m_buffer);
    }

    void Buffer::bind() const
    {
        glBindBuffer(m_bufferType, m_buffer);
    }

    void Buffer::bufferData(void* ptr, size_t size, GLenum type)
    {
        glBufferData(m_bufferType, size, ptr, type);
    }

    void Buffer::bindBase(unsigned int ID) const
    {
        glBindBufferBase(m_bufferType, ID, m_buffer);
    }

    void Buffer::unbind() const
    {
        glBindBuffer(m_bufferType, 0);
    }

    Buffer::~Buffer()
    {
        if (m_buffer)
        {
            glDeleteBuffers(1, &m_buffer);
        }
    }
}