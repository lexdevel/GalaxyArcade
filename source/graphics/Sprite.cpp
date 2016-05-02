#include "Sprite.h"

Sprite::Sprite(const Transformation &transformation, const std::shared_ptr<Texture2D> &texture)
    : Renderable(transformation), m_texture(texture)
{
}

Sprite::~Sprite()
{
}

Rect Sprite::calculateBounds() const
{
    return {
        this->transformation().position.x - this->transformation().scale.x * 2.0f,
        this->transformation().position.y - this->transformation().scale.y * 2.0f,
        this->transformation().scale.x * 2.0f,
        this->transformation().scale.y * 2.0f,
    };
}
