//
// Created by hazardous on 18/03/24.
//

#include "Geometry/Plane.h"

bool Plane::intersect(Ray &ray, Hit &hit, const f32 tmin, const f32 tmax) const {
    const Vector4 normal4 = Vector4(m_normal.get_x(), m_normal.get_y(), m_normal.get_z(), 1);
    if(ray.m_direction.dot(normal4) == 0.0) {
        return false;
    }
    const f32 t = -(ray.m_origin - m_d).dot(normal4) / ray.m_direction.dot(normal4);

    /* if t-distance inside hit is smaller than current hit distance, do nothing */
    /* also discard when hit is outside the frustum ( < near && > far ) */
    if(hit.get_t() < t || t < tmin || t > tmax){
        return false;
    }
    //std::cout << t << " ";
    hit.set_t(t);
    // Calculate the point of intersection
    Vector4 intersection_point = ray.m_origin + ray.m_direction * t;
    hit.m_Point = intersection_point.getVec3();
    //hit.m_Point.normalize();
    // set hit material index to sphere material index
    hit.m_MaterialIndex = m_MaterialIndex;
    hit.set_normal(m_normal);
    hit.didHit = true;
    hit.m_Id = m_Id;
    return true;
}
