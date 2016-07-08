#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

struct Color
{
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

class Image
{
private:
    unsigned int        m_imageW;
    unsigned int        m_imageH;
    std::vector<Color>  m_colorMap;
public:
    Image(unsigned int imageW, unsigned int imageH);
    ~Image();

    static Image *load(const char *filePath);

    inline const unsigned int &imageW() const { return this->m_imageW; }
    inline const unsigned int &imageH() const { return this->m_imageH; }
    inline const Color *colorMap() const { return this->m_colorMap.data(); }
};

#endif // IMAGE_H
