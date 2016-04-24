#ifndef TILE_H
#define TILE_H

#include "../math/Transformation.h"
#include "../math/Vector2f.h"

class Tile
{
private:
    Vector2f m_texindex;
public:
    explicit Tile(const Vector2f &texindex);

    inline Vector2f &texindex() { return this->m_texindex; }
    inline const Vector2f &texindex() const { return this->m_texindex; }
};

#endif // TILE_H
