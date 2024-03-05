#pragma once
#include "Utilities/Macros.h"
#include "Beam/Hit.h"
#include "Beam/Ray.h"
#include <cmath>

class Object3D {
public:
    Object3D() = default;
    virtual ~Object3D() = default;

    virtual void intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const = 0;
    virtual void id() = 0;

    u8 m_color[3]{0, 0, 0};
};
