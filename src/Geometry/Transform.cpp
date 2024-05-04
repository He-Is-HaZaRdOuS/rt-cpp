//
// Created by hazardous on 18/03/24.
//

#include "Geometry/Transform.h"

bool Transform::intersect(Ray &ray, Hit &hit, const f32 tmin, const f32 tmax) const {
    ray.m_origin = m_transform.mult(ray.m_origin);
    ray.m_direction = m_transform.mult(ray.m_direction);
    if(m_object->intersect(ray, hit, tmin, tmax)) {
        const Vector4 normal0 = m_transform_normal.mult({hit.m_Normal.get_x(), hit.m_Normal.get_y(), hit.m_Normal.get_z()});
        hit.m_Normal = {normal0.get_x(), normal0.get_y(), normal0.get_z()};
        // Calculate the point of intersection
        Vector4 intersection_point = ray.m_origin + ray.m_direction * hit.get_t();
        hit.m_Point = intersection_point.getVec3();
        hit.m_Point.normalize();
    }
    return hit.didHit;
}
