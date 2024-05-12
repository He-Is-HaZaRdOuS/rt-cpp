#include "Geometry/Transform.h"

bool Transform::intersect(Ray &ray, Hit &hit, const f32 tmin, const f32 tmax) const {
    ray.m_origin = m_transform.mult(ray.m_origin);
    ray.m_direction = m_transform.mult(ray.m_direction);
    if(m_object->intersect(ray, hit, tmin, tmax)) {
        const Vector4 normal0 = m_transform_normal.mult({hit.m_Normal.get_x(), hit.m_Normal.get_y(), hit.m_Normal.get_z(), 1});
        hit.m_Normal = normal0.getVec3();
        // Calculate the point of intersection
        Vector4 intersection_point = ray.m_origin + ray.m_direction * hit.get_t();
        hit.m_Point = intersection_point.getVec3();
        hit.m_Id = m_Id;
        hit.m_OutwardNormal = ray.m_direction.dot(hit.m_Normal) < 0;
    }
    return hit.didHit;
}
