#include "Rect.h"

bool Rect::isOverlapped(const Rect &rect) const
{
    return (this->x < rect.x + rect.w && this->x + this->w > rect.x &&
            this->y < rect.y + rect.h && this->y + this->h > rect.y);
}
