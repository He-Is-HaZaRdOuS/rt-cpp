#pragma once
#include "Utilities/Macros.h"
#include "Math/Vector3.h"
#include <ostream>

class Matrix3 {
public:
    Matrix3();
    Matrix3(const Matrix3& other);
    Matrix3(f32 f1, f32 f2, f32 f3,
            f32 f4, f32 f5, f32 f6,
            f32 f7, f32 f8, f32 f9);

    ~Matrix3() = default;

    static Matrix3 Zero();

    [[nodiscard]] Vector3 mult(const Vector3& v) const;
    [[nodiscard]] Matrix3 mult(const Matrix3& other) const;
    [[nodiscard]] f32 det() const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix3& matrix);
    friend Matrix3 operator*(const Matrix3& self, const Matrix3& other);
    friend Vector3 operator*(const Matrix3& self, const Vector3& other);

private:
    f32 m_data[3][3];
};
