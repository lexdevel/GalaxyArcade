#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
    float m_data[16]; // 4x4
public:
    Matrix();
    Matrix(const Matrix &matrix);

    /**
     * Create the identity matrix.
     */
    static Matrix identity();

    /**
     * Create the translation matrix.
     * @param x Translation X factor
     * @param y Translation Y factor
     */
    static Matrix translate(float x, float y);

    /**
     * Create the scale matrix.
     * @param x Scale X factor
     * @param y Scale Y factor
     */
    static Matrix scale(float x, float y);

    /**
     * Create the orthographic projection matrix.
     */
    static Matrix orthographic(float left, float top, float right, float bottom);

    Matrix multiply(const Matrix &matrix);

    inline const float *data() const { return this->m_data; }
};

#endif // MATRIX_H
