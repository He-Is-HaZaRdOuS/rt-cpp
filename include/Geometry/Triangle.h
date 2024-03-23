#pragma once
#include <iostream>
#include "Utilities/Macros.h"
#include "Geometry/Object3D.h"
#include "Math/Vector4.h"

class Triangle : public Object3D {
public:
    Triangle() = default;
    Triangle(const Vector4& v1, const Vector4& v2, const Vector4& v3) : m_v1(v1), m_v2(v2), m_v3(v3) {};
    ~Triangle() override = default;
    bool intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const override;
    void id() override {std::cout<<"Triangle\n";};

    Vector4 m_v1;
    Vector4 m_v2;
    Vector4 m_v3;
    Vector3 m_normal;
};
