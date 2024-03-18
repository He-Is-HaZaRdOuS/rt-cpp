#pragma once
#include "Utilities/Macros.h"
#include <ostream>

class Vector3 {
public:
    Vector3();
    Vector3(f32 f1, f32 f2, f32 f3);
    Vector3(const Vector3& other);

    ~Vector3() = default;

    static Vector3 Zero();

    /* Accessors */
    [[nodiscard]] f32 get_x() const { return m_data[0]; }
    [[nodiscard]] f32 get_y() const { return m_data[1]; }
    [[nodiscard]] f32 get_z() const { return m_data[2]; }
    [[nodiscard]] f32 get_r() const { return m_data[0]; }
    [[nodiscard]] f32 get_g() const { return m_data[1]; }
    [[nodiscard]] f32 get_b() const { return m_data[2]; }

    /* Mutators */
    void set_x(f32 x) { m_data[0] = x; }
    void set_y(f32 y) { m_data[1] = y; }
    void set_z(f32 z) { m_data[2] = z; }
    void set_r(f32 r) { m_data[0] = r; }
    void set_g(f32 g) { m_data[1] = g; }
    void set_b(f32 b) { m_data[2] = b; }

    [[nodiscard]] f32 magnitude() const;
    [[nodiscard]] f32 dot(const Vector3& other) const;
    [[nodiscard]] Vector3 cross(const Vector3& other) const;
    void normalize();

    friend std::ostream& operator<<(std::ostream& os, const Vector3& vector);
    friend Vector3 operator+(const Vector3& self, const Vector3& other);
    friend Vector3 operator-(const Vector3& self, const Vector3& other);
    friend Vector3 operator+(const Vector3& self, f32 other);
    friend Vector3 operator*(const Vector3& self, f32 other);
    friend Vector3 operator*( f32 other, const Vector3& self);
    friend Vector3 operator-(const Vector3& self);
    friend Vector3 operator*(const Vector3& self, const Vector3& other);

private:
    f32 m_data[3];
};
