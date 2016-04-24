#ifndef SPRITE_H
#define SPRITE_H

#include "../math/Transformation.h"
#include "../math/Rect.h"
#include "Texture2D.h"

class Sprite
{
private:
    Transformation   m_transformation;
    Texture2D       *m_texture;
public:
    explicit Sprite(Texture2D *texture);

    Rect calculateBounds() const;

    inline Transformation &transformation() { return this->m_transformation; }
    inline Texture2D *texture() { return this->m_texture; }
};

#endif // SPRITE_H
