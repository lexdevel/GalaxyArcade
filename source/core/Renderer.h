#ifndef RENDERER_H
#define RENDERER_H

#include "Renderable.h"

/**
 * The renderer class.
 */
class Renderer
{
protected:
    std::unique_ptr<ShaderProgram> m_renderShader;
protected:
    explicit Renderer();
    virtual ~Renderer();
public:

    /**
     * Create the renderer.
     */
    virtual void create() = 0;

    /**
     *
     * @param w
     * @param h
     */
    virtual void resize(uint32_t w, uint32_t h) = 0;

    /**
     * Initiate the rendering process.
     */
    virtual void initiate() = 0;

    /**
     * Render the specified renderable.
     * @param renderable The renderable
     */
    virtual void render(Renderable *renderable) = 0;

    /**
     * Submit (flush).
     */
    virtual void submit() = 0;
};

#endif // RENDERER_H
