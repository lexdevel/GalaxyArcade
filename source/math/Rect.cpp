#include "Rect.h"

Rect::Rect()
    : x(0.0f), y(0.0f), w(0.0f), h(0.0f)
{
}

Rect::Rect(float x, float y, float w, float h)
    : x(x), y(y), w(w), h(h)
{
}

bool Rect::isOverlapped(const Rect &rect) const
{
    return (this->x < rect.x + rect.w && this->x + this->w > rect.x &&
            this->y < rect.y + rect.h && this->y + this->h > rect.y);
}
