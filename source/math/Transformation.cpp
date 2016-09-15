#include "Transformation.h"

Transformation::Transformation()
    : position(), size()
{
}

Transformation::Transformation(const Vector2f &position, const Vector2f &size)
    : position(position), size(size)
{
}

Matrix Transformation::calculateTransformationMatrix() const
{
    return Matrix::identity()
            .multiply(Matrix::translate(this->position.x, this->position.y))
            .multiply(Matrix::scale(this->size.x, this->size.y));
}
