#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

/**
 * @brief The matrix class for OpenGL transformations.
 */
struct Matrix
{
public:
    float elements[16]; // 4x4
public:
    Matrix();
    Matrix(const Matrix &matrix);

    /**
     * @brief Create the identity matrix.
     */
    static Matrix identity();

    /**
     * Create the translation matrix.
     * @param x The X translation
     * @param y The Y translation
     */
    static Matrix translate(float x, float y);

    /**
     * Create the rotation matrix (for 2D, by Z axis).
     * @param angle  The rotation angle in degrees
     */
    static Matrix rotate(float angle);

    /**
     * Create the scale matrix.
     * @param x The X scale
     * @param y The Y scale
     */
    static Matrix scale(float x, float y);

    /**
     * @brief Create the orthographic projection matrix.
     * @param left The left edge of the projection
     * @param right The right edge of the projection
     * @param bottom The bottom edge of the projection
     * @param top The top edge of the projection
     */
    static Matrix orthographic(float left, float right, float bottom, float top);

    Matrix &operator *=(const Matrix &matrix);
    Matrix  operator  *(const Matrix &matrix);
};

#endif // MATRIX_H
