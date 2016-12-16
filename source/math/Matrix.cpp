#include "Matrix.h"
#include <string.h>

Matrix::Matrix()                     { ::memset(this->elements, 0,               16 * sizeof(float)); }
Matrix::Matrix(const Matrix &matrix) { ::memcpy(this->elements, matrix.elements, 16 * sizeof(float)); }

Matrix Matrix::identity()
{
    auto matrix = Matrix();

    matrix.elements[0 + 0 * 4] = 1.0f;
    matrix.elements[1 + 1 * 4] = 1.0f;
    matrix.elements[2 + 2 * 4] = 1.0f;
    matrix.elements[3 + 3 * 4] = 1.0f;

    return matrix;
}

Matrix Matrix::translate(float x, float y)
{
    auto matrix = Matrix::identity();

    matrix.elements[0 + 3 * 4] = x;
    matrix.elements[1 + 3 * 4] = y;

    return matrix;
}

Matrix Matrix::rotate(float angle)
{
    auto matrix = Matrix::identity();

    const float rad = angle * static_cast<float>(M_PI / 180.0);
    const float sin = ::sinf(rad);
    const float cos = ::cosf(rad);

    matrix.elements[0 + 0 * 4] =  cos;
    matrix.elements[1 + 0 * 4] = -sin;
    matrix.elements[0 + 1 * 4] =  sin;
    matrix.elements[1 + 1 * 4] =  cos;

    return matrix;
}

Matrix Matrix::scale(float x, float y)
{
    auto matrix = Matrix::identity();

    matrix.elements[0 + 0 * 4] = x;
    matrix.elements[1 + 1 * 4] = y;

    return matrix;
}

Matrix Matrix::orthographic(float left, float right, float bottom, float top)
{
    auto matrix = Matrix::identity();

    matrix.elements[0 + 0 * 4] = 2.0f / (right - left);
    matrix.elements[1 + 1 * 4] = 2.0f / (top - bottom);

    matrix.elements[0 + 3 * 4] = (left + right) / (left - right);
    matrix.elements[1 + 3 * 4] = (top + bottom) / (bottom - top);

    return matrix;
}

Matrix Matrix::operator *(const Matrix &matrix)
{
    auto result = Matrix();

    for (auto y = 0; y < 4; ++y) {
        for (auto x = 0; x < 4; ++x) {
            for (auto e = 0; e < 4; ++e) {
                result.elements[x + y * 4] += this->elements[x + e * 4] * matrix.elements[e + y * 4];
            }
        }
    }

    return result;
}

Matrix &Matrix::operator *=(const Matrix &matrix)
{
    float result[16];
    ::memset(result, 0, 16 * sizeof(float));

    for (auto y = 0; y < 4; ++y) {
        for (auto x = 0; x < 4; ++x) {
            for (auto e = 0; e < 4; ++e) {
                result[x + y * 4] += this->elements[x + e * 4] * matrix.elements[e + y * 4];
            }
        }
    }

    ::memcpy(this->elements, result, 16 * sizeof(float));
    return *this;
}
