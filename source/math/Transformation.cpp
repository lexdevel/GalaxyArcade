#include "Transformation.h"

Transformation::Transformation()
    : position(), rotation(0.0f), scale(Vec2(1.0f, 1.0f))
{
}

Transformation::Transformation(const Vec2 &position, float rotation, const Vec2 &scale)
    : position(position), rotation(rotation), scale(scale)
{
}

Matrix Transformation::calculateTransformationMatrix() const
{
    return Matrix::identity()
            * Matrix::translate(-this->position.x, -this->position.y)
            * Matrix::rotate(-this->rotation)
            * Matrix::scale(this->scale.x, this->scale.y);
}
