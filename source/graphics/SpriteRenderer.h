#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "../core/Renderer.h"
#include "../math/Vector2f.h"
#include "SpriteRegion.h"

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
public:
    SpriteRenderer();
    virtual ~SpriteRenderer();

    virtual void create() override;

    virtual void initiate() override;

    virtual void render(Renderable *renderable) override;

    virtual void submit() override;
};

#endif // SPRITERENDERER_H
