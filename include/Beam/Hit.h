#pragma once
#include "Utilities/Macros.h"
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <cfloat>
#include <cstring>

class Hit {
public:
    Hit() = default;
    ~Hit() = default;

    [[nodiscard]] f32 get_t() const { return t; }
    void set_t(f32 newDistance) { this->t = newDistance; }
    void set_color(const Vector3& newColor) { m_color = newColor; }
    void set_normal(const Vector3& newNormal) { m_normal = newNormal; }
    void set_normal(const Vector4& newNormal) { m_normal.set_x(newNormal.get_x()); m_normal.set_y(newNormal.get_y()); m_normal.set_z(newNormal.get_z()); }
    [[nodiscard]] Vector3 getColor() const { return m_color; }
    [[nodiscard]] Vector3 getNormal() const { return m_normal; }

    Vector3 m_color;
    Vector3 m_normal;

private:
    f32 t{FLT_MAX};

};
