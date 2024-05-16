#pragma once
#include "Geometry/Object3D.h"
#include <iostream>

class Cylinder : public virtual Object3D {
public:
    Cylinder() = default;
    ~Cylinder() override = default;

    Cylinder(const f32 radius, const f32 height, const Vector4& center, const Vector4& axis): m_radius(radius), m_height(height) ,m_center(center), m_axis(axis){};

    bool intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const override;
    void id() override {std::cout<<"Cylinder\n";};
    void shift(const Vector4& offset) override;

    f32 m_radius{};
    f32 m_height{};
    Vector4 m_center;
    Vector4 m_axis;
};