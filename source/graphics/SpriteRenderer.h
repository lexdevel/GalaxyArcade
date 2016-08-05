#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "../core/Renderer.h"
#include "Sprite.h"
#include <stack>

struct SpriteRendererShaderParams {
    GLuint a_position = 0;
    GLuint a_texcoord = 0;
    GLuint u_pvmatrix = 0;
    GLuint u_mvmatrix = 0;
    GLuint u_teximage = 0;
};

class SpriteRendererShaderSource
{
public:
    static std::string vertSource();
    static std::string fragSource();
};

/**
 * @brief The sprite renderer class.
 */
class SpriteRenderer : public Renderer
{
private:
    SpriteRendererShaderParams  m_shaderParams;
    Matrix                      m_projection;
    std::stack<Matrix>          m_transformStack;
public:
    explicit SpriteRenderer();
    virtual ~SpriteRenderer();

    virtual void resize(uint32_t w, uint32_t h)  override;

    virtual void initiate(const Matrix &initialTransform = Matrix::identity()) override;

    virtual void render(Renderable *renderable) override;

    virtual void submit() override;
};

#endif // SPRITERENDERER_H
