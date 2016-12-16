#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Matrix.h"
#include "Vec2.h"

/**
 * @brief The transformation structure.
 */
struct Transformation
{
public:
    Vec2    position;
    float   rotation;
    Vec2    scale;
public:
    explicit Transformation();
    explicit Transformation(const Vec2 &position, float rotation = 0.0f, const Vec2 &scale = Vec2(1.0f, 1.0f));

    /**
     * @brief Calculate the transformation matrix.
     */
    Matrix calculateTransformationMatrix() const;
};

#endif // TRANSFORMATION_H
