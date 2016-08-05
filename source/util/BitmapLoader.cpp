#include "BitmapLoader.h"
#include <stb_image.h>

std::shared_ptr<Bitmap> BitmapLoader::load(const std::string &path)
{
    std::shared_ptr<Bitmap> bitmap;

    int32_t w       = 0;
    int32_t h       = 0;
    int32_t format  = 0;

    uint8_t *buffer = stbi_load(path.data(), &w, &h, &format, 0);
    if (buffer != nullptr)
    {
        std::vector<RGBA> data          = std::vector<RGBA>(static_cast<uint32_t>(w * h));
        uint32_t          bufferSize    = static_cast<uint32_t>(w * h * format);
        uint32_t          e             = 0;

        for (uint32_t i = 0; i < bufferSize; i += format)
        {
            RGBA rgba = { 0x00, 0x00, 0x00, 0xFF };
            ::memcpy(&rgba, &buffer[i], static_cast<uint32_t>(format));

            data[e++] = rgba;
        }

        bitmap = std::shared_ptr<Bitmap>(new Bitmap(static_cast<uint32_t>(w), static_cast<uint32_t>(h), data));

        stbi_image_free(buffer);
    }

    return bitmap;
}
