#include "Geometry/Group.h"
#include "Geometry/Sphere.h"

bool Group::intersect(Ray& ray, Hit& hit, const f32 tmin, const f32 tmax) const {
    for(auto const& obj : m_objects) {
        obj->intersect(ray, hit, tmin, tmax);
    }
    return hit.didHit;
}

bool Group::inShadow(Ray& ray, Hit &hit, f32 tmin, f32 tmax) const {
    bool didHit = false;
    for(auto const& obj : m_objects) {
        didHit = obj->intersect(ray, hit, tmin, tmax);
        if(didHit) {
            return true;
        }
    }
    return false;
}
