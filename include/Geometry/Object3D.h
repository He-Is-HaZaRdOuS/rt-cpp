#pragma once
#include "Utilities/Macros.h"
#include "Beam/Hit.h"
#include "Beam/Ray.h"

class Object3D {
public:
    Object3D() = default;
    virtual ~Object3D() = default;

    virtual bool intersect(Ray &ray, Hit& hit, f32 tmin, f32 tmax) const = 0;
    virtual void id() = 0;

    u32 m_MaterialIndex{};
};
