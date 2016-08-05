#include "Transformation.h"

Transformation::Transformation()
    : position(), scale()
{
}

Transformation::Transformation(const Vector2f &position, const Vector2f &scale)
    : position(position), scale(scale)
{
}

Matrix Transformation::calculateTransformationMatrix() const
{
    return Matrix::identity()
            .multiply(Matrix::translate(this->position.x, this->position.y))
            .multiply(Matrix::scale(this->scale.x, this->scale.y));
}
