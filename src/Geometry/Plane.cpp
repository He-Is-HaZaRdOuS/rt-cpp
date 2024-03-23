//
// Created by hazardous on 18/03/24.
//

#include "Geometry/Plane.h"

bool Plane::intersect(const Ray ray, Hit &hit, const f32 tmin, const f32 tmax) const {
    const Vector4 normal4 = Vector4(m_normal.get_x(), m_normal.get_y(), m_normal.get_z(), 1);
    //std::cout << "d: " << m_d << std::endl;
    const f32 t = -(ray.m_origin - m_d).dot(normal4) / ray.m_direction.dot(normal4);



    /* if t-distance inside hit is smaller than current hit distance, do nothing */
    /* also discard when hit is outside the frustum ( < near && > far ) */
    if(hit.get_t() < t || t < tmin || t > tmax){
        return false;
    }

    hit.set_t(t);
    hit.set_color(m_color);
    hit.set_normal(m_normal);
    hit.m_normal.normalize();
    return true;
}
