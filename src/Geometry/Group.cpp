#include "Geometry/Group.h"
#include "Geometry/Sphere.h"

bool Group::intersect(const Ray ray, Hit& hit, const f32 tmin, const f32 tmax) const {
    for(auto const& obj : m_objects) {
        //dynamic_cast<Sphere*>(obj.get())->intersect(ray, hit, tmin, tmax);
        obj->intersect(ray, hit, tmin, tmax);
    }
    return true;
}