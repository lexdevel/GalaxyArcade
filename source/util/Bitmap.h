#ifndef BITMAP_H
#define BITMAP_H

#include "Resource.h"
#include <stdint.h>
#include <vector>

/**
 * @brief The RGBA structure.
 */
struct RGBA {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

/**
 * @brief The bitmap class.
 */
class Bitmap : public Resource
{
private:
    uint32_t            m_w;
    uint32_t            m_h;
    std::vector<RGBA>   m_data;
public:
    explicit Bitmap();
    explicit Bitmap(const Bitmap &bitmap);
    virtual ~Bitmap();

    /**
     * @brief Load the bitmap.
     * @param location The location of the bitmap
     */
    virtual bool load(const std::string &location) override;

    inline const uint32_t &w() const { return this->m_w; }
    inline const uint32_t &h() const { return this->m_h; }
    inline const std::vector<RGBA> &data() const { return this->m_data; }
};

#endif // BITMAP_H
