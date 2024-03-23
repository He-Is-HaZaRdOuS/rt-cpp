#include "Math/Matrix3.h"
#include <cstring>
#include <cmath>

Matrix3::Matrix3() {
    m_data[0][0] = 1.0;
    m_data[0][1] = 0.0;
    m_data[0][2] = 0.0;
    m_data[1][0] = 0.0;
    m_data[1][1] = 1.0;
    m_data[1][2] = 0.0;
    m_data[2][0] = 0.0;
    m_data[2][1] = 0.0;
    m_data[2][2] = 1.0;
}

Matrix3::Matrix3(const Matrix3 &other) {
    memcpy(m_data, other.m_data, sizeof(m_data));
}

Matrix3::Matrix3(const f32 f1, const f32 f2, const f32 f3, const f32 f4, const f32 f5, const f32 f6, const f32 f7, const f32 f8, const f32 f9) {
    m_data[0][0] = f1;
    m_data[1][0] = f2;
    m_data[2][0] = f3;
    m_data[0][1] = f4;
    m_data[1][1] = f5;
    m_data[2][1] = f6;
    m_data[0][2] = f7;
    m_data[1][2] = f8;
    m_data[2][2] = f9;
}

Matrix3 Matrix3::Zero() {
    Matrix3 tmp = Matrix3();
    tmp.m_data[0][0] = 0.0;
    tmp.m_data[1][1] = 0.0;
    tmp.m_data[2][2] = 0.0;
    return tmp;
}

Vector3 Matrix3::mult(const Vector3& v) const
{
    return { m_data[0][0] * v.get_x() + m_data[0][1] * v.get_y() + m_data[0][2] * v.get_z(),
             m_data[1][0] * v.get_x() + m_data[1][1] * v.get_y() + m_data[1][2] * v.get_z(),
             m_data[2][0] * v.get_x() + m_data[2][1] * v.get_y() + m_data[2][2] * v.get_z() };
}

Matrix3 Matrix3::mult(const Matrix3 &other) const {
    Matrix3 tmp = Matrix3::Zero();

    for (u32 i = 0; i < 3; ++i) {
        for (u32 k = 0; k < 3; ++k) {
            for (u32 j = 0; j < 3; ++j) {
                tmp.m_data[i][j] = tmp.m_data[i][j] + m_data[i][k] * other.m_data[k][j];
            }
        }
    }

    return tmp;
}

f32 Matrix3::det() const
{
    f32 det = 0.0f;

    det += m_data[0][0] * (m_data[1][1] * m_data[2][2] - m_data[1][2] * m_data[2][1]);
    det -= m_data[0][1] * (m_data[1][0] * m_data[2][2] - m_data[1][2] * m_data[2][0]);
    det += m_data[0][2] * (m_data[1][0] * m_data[2][1] - m_data[1][1] * m_data[2][0]);

    return det;
}

std::ostream& operator<<(std::ostream& os, const Matrix3& matrix)
{
    os << "[";
    for (u32 i = 0; i < 3; ++i) {
        os << "[";
        for (u32 j = 0; j < 3; ++j) {
            os << matrix.m_data[i][j];
            if (j != 2)
                os << ", ";
        }
        os << "]";
    }
    os << "]";
    return os;
}

Matrix3 operator*(const Matrix3& self, const Matrix3& other)
{
    return self.mult(other);
}

Vector3 operator*(const Matrix3& self, const Vector3& other)
{
    return self.mult(other);
}

Matrix3 Matrix3::inverse() const {
    const f32 detr = det();
    const f32 invdetr = 1 / detr;

    Matrix3 tmp = Matrix3();

    tmp.m_data[0][0] = (m_data[1][1] * m_data[2][2] - m_data[2][1] * m_data[1][2]) * invdetr;
    tmp.m_data[0][1] = (m_data[0][2] * m_data[2][1] - m_data[0][1] * m_data[2][2]) * invdetr;
    tmp.m_data[0][2] = (m_data[0][1] * m_data[1][2] - m_data[0][2] * m_data[1][1]) * invdetr;
    tmp.m_data[1][0] = (m_data[1][2] * m_data[2][0] - m_data[1][0] * m_data[2][2]) * invdetr;
    tmp.m_data[1][1] = (m_data[0][0] * m_data[2][2] - m_data[0][2] * m_data[2][0]) * invdetr;
    tmp.m_data[1][2] = (m_data[1][0] * m_data[0][2] - m_data[0][0] * m_data[1][2]) * invdetr;
    tmp.m_data[2][0] = (m_data[1][0] * m_data[2][1] - m_data[2][0] * m_data[1][1]) * invdetr;
    tmp.m_data[2][1] = (m_data[2][0] * m_data[0][1] - m_data[0][0] * m_data[2][1]) * invdetr;
    tmp.m_data[2][2] = (m_data[0][0] * m_data[1][1] - m_data[1][0] * m_data[0][1]) * invdetr;

    return tmp;
}

Matrix3 Matrix3::transpose() const {
    Matrix3 tmp = Matrix3();

    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            tmp.m_data[i][j] = m_data[j][i];
        }
    }

    return tmp;
}
