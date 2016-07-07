#include "Buffer.h"

Buffer::Buffer(const BufferTarget &target)
    : m_target(target)
{
    GLCALL(glGenBuffers(1, &this->m_identifier));
}

Buffer::~Buffer()
{
    if (this->m_identifier != 0)
    {
        GLCALL(glDeleteBuffers(1, &this->m_identifier));
        this->m_identifier = 0;
    }
}

void Buffer::attach() { GLCALL(glBindBuffer(this->m_target, this->m_identifier)); }
void Buffer::detach() { GLCALL(glBindBuffer(this->m_target, 0)); }
