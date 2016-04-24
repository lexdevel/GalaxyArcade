#ifndef TILERENDERER_H
#define TILERENDERER_H

#include "../graphics/GraphicsFactory.h"
#include "Tile.h"

// ToDo: TileVertex is the same as SpriteVertex - reuse or create one
// ToDo: Create abstract entity for renderers

class TileRenderer
{
private:
    unsigned int m_tileXCount;
    unsigned int m_tileYCount;

    std::unique_ptr<ShaderProgram> m_renderShader;
    std::unique_ptr<Buffer> m_vertexBuffer;
    std::unique_ptr<Buffer> m_coordsBuffer;
    std::unique_ptr<Buffer> m_elementArray;
    std::unique_ptr<Texture2D> m_textureAtlas;
public:
    TileRenderer(unsigned int tileXCount, unsigned int tileYCount, Texture2D *textureAtlas);

    bool create();

    void render(const Transformation &transformation, Tile *tile);
};

#endif // TILERENDERER_H
