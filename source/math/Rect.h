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
    Rect();
    Rect(float x, float y, float w, float h);

    bool isOverlapped(const Rect &rect) const;
};

#endif // RECT_H
