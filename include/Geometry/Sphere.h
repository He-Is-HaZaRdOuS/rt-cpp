#pragma once
#include "Geometry/Object3D.h"
#include <iostream>

class Sphere : public virtual Object3D {
public:
    Sphere() = default;
    ~Sphere() override = default;

    Sphere(f32 radius, Vector4 center): m_radius(radius), m_center(center){};

    void intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const override;
    void id() override {std::cout<<"Sphere\n";};

    f32 m_radius;
    Vector4 m_center;
};