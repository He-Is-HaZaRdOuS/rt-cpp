#pragma once
#include "Macros.h"
#include "Geometry/Object3D.h"
#include <iostream>
#include <vector>
#include <memory>

class Group : public Object3D {
public:
    f32 intersect(Ray ray, Hit hit, f32 tmin) override;
    void id() override{std::cout<<"Group\n";};

    std::vector<std::shared_ptr<Object3D>> objects;
};