#ifndef SPRITE_H
#define SPRITE_H

#include "../core/Renderable.h"
#include "../math/Transformation.h"
#include "../math/Rect.h"

class Sprite : public Renderable
{
protected:
    Transformation              m_transformation;
    std::auto_ptr<Texture2D>    m_texture;
public:
    explicit Sprite(const Transformation &transformation, Texture2D *texture);
    virtual ~Sprite();

    Rect calculateBounds() const;

    inline Transformation &transformation() { return this->m_transformation; }
    inline Texture2D *texture() { return this->m_texture.get(); }
};

#endif // SPRITE_H
