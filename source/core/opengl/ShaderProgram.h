#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "../GraphicsObject.h"

/**
 * The shader program class.
 */
class ShaderProgram : public GraphicsObject
{
private:
    explicit ShaderProgram(const GLuint &identifier);
public:
    virtual ~ShaderProgram();

    /**
     * Attach.
     */
    virtual void attach() override;

    /**
     * Detach.
     */
    virtual void detach() override;

    friend class GraphicsFactory;
};

#endif // SHADERPROGRAM_H
