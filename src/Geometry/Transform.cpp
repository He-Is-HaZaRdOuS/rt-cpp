//
// Created by hazardous on 18/03/24.
//

#include "Geometry/Transform.h"

bool Transform::intersect(Ray ray, Hit &hit, const f32 tmin, const f32 tmax) const {
    ray.m_origin = m_transform.mult(ray.m_origin);
    ray.m_direction = m_transform.mult(ray.m_direction);
    if(m_object->intersect(ray, hit, tmin, tmax)) {
        const Vector4 normal0 = m_transform_normal.mult({hit.m_normal.get_x(), hit.m_normal.get_y(), hit.m_normal.get_z()});
        hit.m_normal = {normal0.get_x(), normal0.get_y(), normal0.get_z()};
    }
    return true;
}
