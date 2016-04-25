#include "Transformation.h"

Transformation::Transformation()
    : position(), scale()
{
}

Transformation::Transformation(const Vector2f &position, const Vector2f &scale)
    : position(position), scale(scale)
{
}

Matrix Transformation::createTransformationMatrix() const
{
    Matrix matrix = Matrix::identity();

    matrix = matrix.multiply(Matrix::translate(this->position.x, this->position.y));
    matrix = matrix.multiply(Matrix::scale(this->scale.x, this->scale.y));

    return matrix;
}
