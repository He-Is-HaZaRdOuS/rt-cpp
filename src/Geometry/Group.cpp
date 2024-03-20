#include "Geometry/Group.h"
#include "Geometry/Sphere.h"

void Group::intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const {
    for(auto const& obj : m_objects) {
        //dynamic_cast<Sphere*>(obj.get())->intersect(ray, hit, tmin, tmax);
        obj->intersect(ray, hit, tmin, tmax);
    }
}