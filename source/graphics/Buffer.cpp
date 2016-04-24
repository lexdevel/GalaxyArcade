#include "Buffer.h"
#include <OpenGL/gl.h>

Buffer::Buffer(const GLuint &identifier, GLenum target)
    : GraphicsObject(identifier), m_target(target)
{
}

Buffer::~Buffer()
{
}

void Buffer::attach() { GLCALL(glBindBuffer(this->m_target, this->identifier())); }
void Buffer::detach() { GLCALL(glBindBuffer(this->m_target, 0)); }
