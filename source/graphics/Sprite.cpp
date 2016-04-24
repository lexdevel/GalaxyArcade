#include "Sprite.h"

Sprite::Sprite(Texture2D *texture)
    : m_texture(texture)
{
}

Rect Sprite::calculateBounds() const
{
    return {
        this->m_transformation.position.x - this->m_transformation.scale.x,
        this->m_transformation.position.y - this->m_transformation.scale.y,
        this->m_transformation.scale.x,
        this->m_transformation.scale.y,
    };
}
