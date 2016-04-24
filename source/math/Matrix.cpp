#include "Matrix.h"
#include <string.h>

Matrix::Matrix()                     { memset(this->m_data, 0,             16 * sizeof(float)); }
Matrix::Matrix(const Matrix &matrix) { memcpy(this->m_data, matrix.m_data, 16 * sizeof(float)); }

Matrix Matrix::identity()
{
    Matrix matrix;

    matrix.m_data[0 + 0 * 4] = 1.0f;
    matrix.m_data[1 + 1 * 4] = 1.0f;
    matrix.m_data[2 + 2 * 4] = 1.0f;
    matrix.m_data[3 + 3 * 4] = 1.0f;

    return matrix;
}

Matrix Matrix::translate(float x, float y)
{
    Matrix matrix = Matrix::identity();

    matrix.m_data[0 + 3 * 4] = x;
    matrix.m_data[1 + 3 * 4] = y;

    return matrix;
}

Matrix Matrix::scale(float x, float y)
{
    Matrix matrix = Matrix::identity();

    matrix.m_data[0 + 0 * 4] = x;
    matrix.m_data[1 + 1 * 4] = y;

    return matrix;
}

Matrix Matrix::orthographic(float left, float top, float right, float bottom)
{
    Matrix matrix = Matrix::identity();

    matrix.m_data[0 + 0 * 4] = 2.0f / (right - left);
    matrix.m_data[1 + 1 * 4] = 2.0f / (top - bottom);

    matrix.m_data[0 + 3 * 4] = (left + right) / (left - right);
    matrix.m_data[1 + 3 * 4] = (top + bottom) / (bottom - top);

    return matrix;
}

Matrix Matrix::multiply(const Matrix &matrix)
{
    Matrix result;

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            for (int e = 0; e < 4; ++e) {
                result.m_data[x + y * 4] += this->m_data[x + e * 4] * matrix.m_data[e + y * 4];
            }
        }
    }

    return result;
}
