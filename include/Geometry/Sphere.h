#pragma once
#include "Macros.h"
#include "Geometry/Object3D.h"
#include <iostream>

class Sphere : public Object3D {
public:
    Sphere() = default;
    ~Sphere() override = default;

    Sphere(f32 radius, Vector4 center): m_radius(radius), m_center(center){};

    f32 intersect(Ray ray, Hit hit, f32 tmin) override;
    void id() override {std::cout<<"Sphere\n";};

    f32 m_radius;
    Vector4 m_center;
};