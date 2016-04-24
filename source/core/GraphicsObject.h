#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#ifdef OS_APPLE
    #include <OpenGL/gl.h>
#endif

#include <iostream>
#include "Attachable.h"

#ifdef DEBUG
    #define GLCALL(X)   X; do { GLenum code = GL_NO_ERROR;                                                             \
                                if ((code = glGetError()) != GL_NO_ERROR) { std::cerr << "GL ERROR ON (" << #X << ")"  \
                                    << ": " << __LINE__ << ":" << __FILE__ << ":" << __FUNCTION__ << std::endl; }      \
                        } while (0)
#else
    #define GLCALL(X)   X
#endif

/**
 * The abstract graphics object class.
 */
class GraphicsObject : public Attachable
{
private:
    GLuint m_identifier;
protected:
    explicit GraphicsObject(const GLuint &identifier);
    virtual ~GraphicsObject();
public:

    /**
     * Attach.
     */
    virtual void attach() = 0;

    /**
     * Detach.
     */
    virtual void detach() = 0;

    inline const GLuint &identifier() const { return this->m_identifier; }
};

#endif // GRAPHICSOBJECT_H
