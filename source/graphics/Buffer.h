#ifndef BUFFER_H
#define BUFFER_H

#include "../core/GraphicsObject.h"

class Buffer : public GraphicsObject
{
private:
    GLenum m_target;
private:
    Buffer(const GLuint &identifier, GLenum target);
public:
    virtual ~Buffer();

    /**
     * Attach.
     */
    virtual void attach() override;

    /**
     * Detach.
     */
    virtual void detach() override;

    inline const GLenum &target() const { return this->m_target; }

    friend class GraphicsFactory;
};

#endif // BUFFER_H
