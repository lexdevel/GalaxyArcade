#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Matrix.h"
#include "Vector2f.h"

struct Transformation
{
public:
    Vector2f position;
    Vector2f scale;
public:
    Transformation();
    Transformation(const Vector2f &position, const Vector2f &scale);

    /**
     * @brief Calculate the transformation matrix.
     */
    Matrix calculateTransformationMatrix() const;
};

#endif // TRANSFORMATION_H
