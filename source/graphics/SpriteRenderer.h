#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <memory>
#include "../math/Transformation.h"
#include "GraphicsFactory.h"

struct SpriteVertex
{
public:
    Vector2f position;
    Vector2f texcoord;
};

class SpriteRenderer
{
private:
    std::unique_ptr<ShaderProgram>  m_renderShader;
    std::unique_ptr<Buffer>         m_vertexBuffer;
    std::unique_ptr<Buffer>         m_elementArray;
public:

    static SpriteRenderer *create();

    void render(const Transformation &transformation, Texture2D *texture);
};

#endif // SPRITERENDERER_H
