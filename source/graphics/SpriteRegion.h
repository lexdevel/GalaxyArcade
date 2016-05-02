#ifndef SPRITEREGION_H
#define SPRITEREGION_H

#include <stdint.h>
#include "Sprite.h"
#include "../math/Transformation.h"

class SpriteRegion : public Sprite
{
private:
    uint32_t m_rows;
    uint32_t m_cols;
    uint32_t m_x;
    uint32_t m_y;
public:
    SpriteRegion(uint32_t rows, uint32_t cols, uint32_t x, uint32_t y,
                 const Transformation &transformation, const std::shared_ptr<Texture2D> &texture);
    virtual ~SpriteRegion();

    inline uint32_t &rows() { return this->m_rows; }
    inline uint32_t &cols() { return this->m_cols; }
    inline uint32_t &x() { return this->m_x; }
    inline uint32_t &y() { return this->m_y; }
};

#endif // SPRITEREGION_H
