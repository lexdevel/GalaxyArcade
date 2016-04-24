#ifndef RECT_H
#define RECT_H

struct Rect
{
public:
    float x;
    float y;
    float w;
    float h;
public:

    bool isOverlapped(const Rect &rect) const;
};

#endif // RECT_H
