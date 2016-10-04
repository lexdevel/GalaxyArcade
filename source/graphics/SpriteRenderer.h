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
    glm::mat4                   m_projection;
    std::stack<glm::mat4>       m_transformStack;
public:
    explicit SpriteRenderer();
    virtual ~SpriteRenderer();

    virtual void resize(uint32_t w, uint32_t h)  override;

    virtual void invalidate(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) override;

    virtual void initiate(const glm::mat4 &initialTransform = glm::mat4(1.0f)) override;

    virtual void render(Renderable *renderable) override;

    virtual void submit() override;
};

#endif // SPRITERENDERER_H
