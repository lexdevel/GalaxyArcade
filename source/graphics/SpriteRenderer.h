#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "../core/Renderer.h"
#include "../math/Vector2f.h"
#include "SpriteRegion.h"

struct Viewport
{
public:
    uint32_t w = 0;
    uint32_t h = 0;
};

struct SpriteRendererShaderParams
{
public:
    GLuint  a_position = 0;
    GLuint  a_texcoord = 0;
    GLuint  u_pvmatrix = 0;
    GLuint  u_mvmatrix = 0;
    GLuint  u_teximage = 0;
};

class SpriteRenderer : public Renderer
{
private:
    std::unique_ptr<Buffer>     m_vertexBuffer;
    std::unique_ptr<Buffer>     m_coordsBuffer;
    std::unique_ptr<Buffer>     m_elementArray;
    SpriteRendererShaderParams  m_shaderParams;
    Viewport m_viewport;
public:
    SpriteRenderer();
    virtual ~SpriteRenderer();

    virtual void create() override;

    virtual void resize(uint32_t w, uint32_t h) override;

    virtual void initiate() override;

    virtual void render(Renderable *renderable) override;

    virtual void submit() override;
};

#endif // SPRITERENDERER_H
