#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Matrix.h"
#include "Vector2f.h"

struct Transformation
{
public:
    Vector2f position;
    // float    rotation;   // No need for this game
    Vector2f scale;
public:

    Matrix createTransformationMatrix() const;
};

#endif // TRANSFORMATION_H
