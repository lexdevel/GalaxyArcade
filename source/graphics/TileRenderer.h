#ifndef TILERENDERER_H
#define TILERENDERER_H

#include "Tile.h"

class TileRenderer
{
private:
    unsigned int m_tileXCount;
    unsigned int m_tileYCount;

    
public:
    TileRenderer(unsigned int tileXCount, unsigned int tileYCount, Texture2D *textureAtlas);

    void render(Tile *tile);
};

#endif // TILERENDERER_H
