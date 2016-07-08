#ifndef PLATFORMENTITY_H
#define PLATFORMENTITY_H

#ifdef OS_APPLE
#include <OpenGL/gl.h>
#endif

#ifdef OS_WIN32
#include <GLXW/glxw.h>
#endif

#include <iostream>
#include <stdint.h>
// #include <assert.h>
#include <string>
#include <memory>

#ifdef DEBUG
    #define GLCALL(STMT)    do {                                                                \
                                STMT; GLenum code = glGetError();                               \
                                if (code != GL_NO_ERROR) {                                      \
                                    std::cerr << "OpenGL CALL FAILED WITH CODE " << code        \
                                              << " ( " << #STMT << " )"          << std::endl;  \
                                }                                                               \
                            } while (0)
#else
    #define GLCALL(STMT)    STMT
#endif

/**
 * @brief The abstract platform entity class.
 */
class PlatformEntity
{
protected:
    GLuint m_identifier;
public:
    explicit PlatformEntity(const GLuint &identifier = 0);
    virtual ~PlatformEntity() = 0;

    virtual void attach() = 0;
    virtual void detach() = 0;

    inline const GLuint &identifier() const { return this->m_identifier; }
};

#endif // PLATFORMENTITY_H
