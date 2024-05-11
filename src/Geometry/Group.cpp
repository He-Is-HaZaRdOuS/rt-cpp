#include "Geometry/Group.h"

#include <complex>


#include "Geometry/Sphere.h"

bool Group::intersect(Ray& ray, Hit& hit, const f32 tmin, const f32 tmax) const {
    for(auto const& obj : m_objects) {
        obj->intersect(ray, hit, tmin, tmax);
    }
    return hit.didHit;
}

bool Group::inShadow(Ray& ray, Hit &hit, Hit& mainHit, f32 tmin, f32 tmax) const {
    bool didHit = false;
    for(auto const& obj : m_objects) {
        didHit = obj->intersect(ray, hit, tmin, tmax);
        if(didHit && hit.m_Id != mainHit.m_Id) {
            //std::cout << hit.get_t() << " \n";
            return true;
        }
    }
    return false;
}
