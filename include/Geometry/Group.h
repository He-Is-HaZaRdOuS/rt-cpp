#pragma once
#include "Geometry/Object3D.h"
#include <iostream>
#include <vector>
#include <memory>

class Group : public virtual Object3D {
public:
    bool intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const override;
    bool inShadow(Ray& ray, Hit& hit, Hit& mainHit, f32 tmin, f32 tmax) const;
    void id() override{std::cout<<"Group\n";};
    void shift(const Vector4& offset) override;

    std::vector<std::shared_ptr<Object3D>> m_objects;
};