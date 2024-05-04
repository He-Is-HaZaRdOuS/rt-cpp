#pragma once
#include "Utilities/Macros.h"
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <cfloat>

class Hit {
public:
    Hit() = default;
    ~Hit() = default;

    [[nodiscard]] f32 get_t() const { return t; }
    void set_t(f32 newDistance) { this->t = newDistance; }
    void set_normal(const Vector3& newNormal) { m_Normal = newNormal; }
    void set_normal(const Vector4& newNormal) { m_Normal.set_x(newNormal.get_x()); m_Normal.set_y(newNormal.get_y()); m_Normal.set_z(newNormal.get_z()); }
    [[nodiscard]] Vector3 getNormal() const { return m_Normal; }

    u32 m_MaterialIndex{};
    Vector3 m_Point;
    Vector3 m_Normal;
    bool didHit = false;

private:
    f32 t{FLT_MAX};

};
