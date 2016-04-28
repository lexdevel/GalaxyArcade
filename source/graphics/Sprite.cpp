#include "Sprite.h"

Sprite::Sprite(const Transformation &transformation, Texture2D *texture)
    : m_transformation(transformation), m_texture(texture)
{
}

Sprite::~Sprite()
{
}

Rect Sprite::calculateBounds() const
{
    return {
        this->m_transformation.position.x - this->m_transformation.scale.x * 2.0f,
        this->m_transformation.position.y - this->m_transformation.scale.y * 2.0f,
        this->m_transformation.scale.x * 2.0f,
        this->m_transformation.scale.y * 2.0f,
    };
}
