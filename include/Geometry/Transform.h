#pragma once
#include "Utilities/Macros.h"
#include "Geometry/Object3D.h"
#include "Math/Matrix4.h"
#include <memory>
#include <iostream>

class Transform : public virtual Object3D {
public:
    Transform() = default;
    Transform(const Matrix4& m, const std::shared_ptr<Object3D>& object) : m_transform(m) {
        m_object = object;
    }
    ~Transform() override = default;
    bool intersect(Ray &ray, Hit& hit, f32 tmin, f32 tmax) const override;
    void id() override {std::cout<<"Transform\n";};

    Matrix4 m_transform = Matrix4();
    Matrix4 m_translate = Matrix4();
    Matrix4 m_rotatex = Matrix4();
    Matrix4 m_rotatey = Matrix4();
    Matrix4 m_rotatez = Matrix4();
    Matrix4 m_scale = Matrix4();
    Matrix4 m_transform_normal = Matrix4();
    std::shared_ptr<Object3D> m_object;
};
