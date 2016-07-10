#ifndef BUFFER_H
#define BUFFER_H

#include "core/PlatformEntity.h"

enum BufferTarget : GLenum {
    VERTEXBUFFER = GL_ARRAY_BUFFER,
    ELEMENTARRAY = GL_ELEMENT_ARRAY_BUFFER
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
};

#endif // BUFFER_H
