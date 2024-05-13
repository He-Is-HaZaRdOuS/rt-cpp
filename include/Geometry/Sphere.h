#pragma once
#include "Geometry/Object3D.h"
#include <iostream>

class Sphere : public virtual Object3D {
public:
    Sphere() = default;
    ~Sphere() override = default;

    Sphere(const f32 radius, const Vector4& center): m_radius(radius), m_center(center){};

    bool intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const override;
    void id() override {std::cout<<"Sphere\n";};
    void shift(const Vector4& offset) override;

    f32 m_radius{};
    Vector4 m_center;
};