#include "Bitmap.h"
#include <stb/stb_image.h>

Bitmap::Bitmap()
    : m_w(0), m_h(0), m_data(0)
{
}

Bitmap::Bitmap(const Bitmap &bitmap)
    : m_w(bitmap.m_w), m_h(bitmap.m_h), m_data(bitmap.m_data)
{
}

Bitmap::~Bitmap()
{
}

bool Bitmap::load(const std::string &location)
{
    int32_t w       = 0;
    int32_t h       = 0;
    int32_t format  = 0;

    auto buffer = stbi_load(location.data(), &w, &h, &format, 0);
    if (!buffer)
    {
        return false;
    }

    uint32_t bufferLength   = static_cast<uint32_t>(w * h * format);
    uint32_t e              = 0;

    this->m_w = static_cast<uint32_t>(w);
    this->m_h = static_cast<uint32_t>(h);
    this->m_data.resize(bufferLength);

    for (uint32_t i = 0; i < bufferLength; i += static_cast<uint32_t>(format))
    {
        RGBA rgba = { 0x00, 0x00, 0x00, 0xFF };
        ::memcpy(&rgba, &buffer[i], static_cast<uint32_t>(format));

        this->m_data[e++] = rgba;
    }

    stbi_image_free(buffer);
    return true;
}
