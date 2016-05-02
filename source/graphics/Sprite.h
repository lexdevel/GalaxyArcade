#ifndef SPRITE_H
#define SPRITE_H

#include "../core/Renderable.h"
#include "../math/Transformation.h"
#include "../math/Rect.h"

class Sprite : public Renderable
{
protected:
    std::shared_ptr<Texture2D> m_texture;
public:
    explicit Sprite(const Transformation &transformation, const std::shared_ptr<Texture2D> &texture);
    virtual ~Sprite();

    Rect calculateBounds() const;

    inline Texture2D *texture() { return this->m_texture.get(); }
};

#endif // SPRITE_H
