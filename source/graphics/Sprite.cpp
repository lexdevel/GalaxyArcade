#include "Sprite.h"

Sprite::Sprite(const Transformation &transformation,
               const std::shared_ptr<Texture2D> &textureImage)
    : Renderable(SpriteBuffer::instance()->vertexBuffer(), SpriteBuffer::instance()->elementArray()),
      m_transformation(transformation),
      m_textureImage(textureImage),
      m_texelsBuffer(SpriteBuffer::instance()->texelsBuffer())
{
}

Sprite::~Sprite()
{
}
