#ifndef RENDERER_H
#define RENDERER_H

#include "../platform/ShaderProgram.h"
#include "../math/Matrix.h"
#include "Renderable.h"

/**
 * @brief The renderer interface.
 */
class Renderer
{
protected:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
public:
    explicit Renderer(const std::shared_ptr<ShaderProgram> &shaderProgram);
    virtual ~Renderer() = 0;

    /**
     * @brief Initiate the rendering process.
     * @param initialTransform The initial transformation matrix
     */
    virtual void initiate(const Matrix &initialTransform = Matrix::identity()) = 0;

    /**
     * @brief Render the specified renderable.
     * @param The specified renderable
     */
    virtual void render(Renderable *renderable) = 0;

    /**
     * @brief Submit the rendering process.
     */
    virtual void submit() = 0;
};

#endif // RENDERER_H
