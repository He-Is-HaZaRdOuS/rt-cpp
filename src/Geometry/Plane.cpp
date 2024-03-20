//
// Created by hazardous on 18/03/24.
//

#include "Geometry/Plane.h"

void Plane::intersect(Ray ray, Hit &hit, f32 tmin, f32 tmax) const {
    Vector4 normal4 = Vector4(m_normal.get_x(), m_normal.get_y(), m_normal.get_z(), 1);
    //std::cout << "d: " << m_d << std::endl;
    f32 t = -(ray.m_origin - m_d).dot(normal4) / ray.m_direction.dot(normal4);



    /* if t-distance inside hit is smaller than current hit distance, do nothing */
    /* also discard when hit is outside the frustum ( < near && > far ) */
    if(hit.get_t() < t || t < tmin || t > tmax){
        return;
    }

    hit.set_t(t);
    hit.set_color(m_color);
    hit.set_normal(m_normal);
    hit.m_normal.normalize();
    return;
}
