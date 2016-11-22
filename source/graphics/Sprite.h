#ifndef SPRITE_H
#define SPRITE_H

#include "../math/Transformation.h"
#include "../platform/Texture2D.h"
#include "../core/Renderable.h"
#include "SpriteBuffer.h"

/**
 * @brief The sprite class.
 */
class Sprite : public Renderable
{
private:
    Transformation                  m_transformation;
    std::shared_ptr<Texture2D>      m_textureImage;
    std::shared_ptr<VertexBuffer>   m_texelsBuffer;
public:
    explicit Sprite(const Transformation &transformation,
                    const std::shared_ptr<Texture2D> &textureImage);
    virtual ~Sprite();

    inline Transformation &transformation() { return this->m_transformation; }
    inline VertexBuffer *texelsBuffer() { return this->m_texelsBuffer.get(); }
    inline Texture2D *textureImage() { return this->m_textureImage.get(); }
};

#endif // SPRITE_H
