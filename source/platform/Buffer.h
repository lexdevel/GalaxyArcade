#ifndef BUFFER_H
#define BUFFER_H

#include "core/PlatformEntity.h"

enum BufferTarget : GLenum {
    VERTEXBUFFER = GL_ARRAY_BUFFER,
    ELEMENTARRAY = GL_ELEMENT_ARRAY_BUFFER
};

enum BufferDraw : GLenum {
    STATIC       = GL_STATIC_DRAW,
    STREAM       = GL_STREAM_DRAW,
    DYNAMIC      = GL_DYNAMIC_DRAW
};

/**
 * @brief The buffer class.
 */
class Buffer : public PlatformEntity
{
private:
    BufferTarget m_target;
public:
    explicit Buffer(const BufferTarget &target);
    virtual ~Buffer();

    virtual void attach() override;
    virtual void detach() override;

    template<typename T> void bufferData(const std::vector<T> &buffer, const BufferDraw &draw = BufferDraw::STATIC)
    {
        GLCALL(glBindBuffer(this->m_target, this->m_identifier));
        GLCALL(glBufferData(this->m_target, sizeof(T) * static_cast<GLsizeiptr>(buffer.size()), buffer.data(), draw));
        GLCALL(glBindBuffer(this->m_target, 0));
    }
};

#endif // BUFFER_H
