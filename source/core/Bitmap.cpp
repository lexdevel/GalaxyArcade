#include "Bitmap.h"
#include <string.h>

Bitmap::Bitmap(uint32_t w, uint32_t h)
    : m_w(w), m_h(h), m_data(w * h)
{
    for (unsigned int i = 0; i < this->m_data.size(); i++) {
        //                  R     G     B     A
        this->m_data[i] = { 0x00, 0x00, 0x00, 0xFF };
    }
}

Bitmap::Bitmap(uint32_t w, uint32_t h, const std::vector<RGBA> &data)
    : m_w(w), m_h(h), m_data(data)
{
}

Bitmap::Bitmap(const Bitmap &bitmap)
    : m_w(bitmap.m_w), m_h(bitmap.m_h), m_data(bitmap.m_data)
{
}

Bitmap::~Bitmap()
{
}
