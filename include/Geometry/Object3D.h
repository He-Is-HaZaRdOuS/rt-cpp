#pragma once
#include "Beam/Hit.h"
#include "Beam/Ray.h"

class Object3D {
public:
    Object3D() = default;
    virtual ~Object3D() = default;

    virtual f32 intersect(Ray ray, Hit hit, f32 tmin) = 0;
    virtual void id() = 0;

    f32 m_color[3]{0.0, 0.0, 0.0};
};
