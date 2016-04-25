#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION 1
#include <stb_image.h>

Image::Image(unsigned int imageW, unsigned int imageH)
    : m_imageW(imageW), m_imageH(imageH), m_colorMap(imageW * imageH)
{

}

Image::~Image()
{
}

Image *Image::load(const char *filePath)
{
    int imageW   = 0;
    int imageH   = 0;
    int imageBpp = 0;

    // stbi_set_flip_vertically_on_load(1);
    unsigned char *buffer = stbi_load(filePath, &imageW, &imageH, &imageBpp, 0);

    if (!buffer) {
        return nullptr;
    }

    Image *image = new Image(imageW, imageH);

    unsigned int length = static_cast<unsigned int>(imageW * imageH * imageBpp);
    unsigned int e = 0;
    for (unsigned int i = 0; i < length; i += imageBpp)
    {
        Color color = { 0x00, 0x00, 0x00, 0xFF };
        memcpy(&color, &buffer[i], imageBpp);

        image->m_colorMap[e++] = color;
    }

    stbi_image_free(buffer);
    return image;
}
