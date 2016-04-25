#include "SpriteRegion.h"

SpriteRegion::SpriteRegion(uint32_t rows, uint32_t cols, uint32_t x, uint32_t y,
                           const Transformation &transformation, Texture2D *texture)
    : m_rows(rows), m_cols(cols), m_x(x), m_y(y), Sprite(transformation, texture)
{
}

SpriteRegion::~SpriteRegion()
{
}
