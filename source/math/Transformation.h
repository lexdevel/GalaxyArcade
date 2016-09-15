#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Matrix.h"
#include "Vector2f.h"

struct Transformation
{
public:
    Vector2f position;
    Vector2f size;
public:
    Transformation();
    Transformation(const Vector2f &position, const Vector2f &size);

    /**
     * @brief Calculate the transformation matrix.
     */
    Matrix calculateTransformationMatrix() const;
};

#endif // TRANSFORMATION_H
