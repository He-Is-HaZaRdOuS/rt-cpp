#pragma once
#include "Utilities/Macros.h"
#include "Math/Vector3.h"
#include "Beam/Hit.h"
#include "Beam/Ray.h"
#include <cmath>

class Object3D {
public:
    Object3D() = default;
    virtual ~Object3D() = default;

    virtual void intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const = 0;
    virtual void id() = 0;

    void set_color(const f32 newColor[]) { m_color.set_r(newColor[0]); m_color.set_g(newColor[1]); m_color.set_b(newColor[2]);}
    void set_color(const Vector3& newColor) { m_color = newColor; }
    f32 get_r() { return m_color.get_r(); };
    f32 get_g() { return m_color.get_g(); };
    f32 get_b() { return m_color.get_b(); };

protected:
    Vector3 m_color;
};
