#include "Geometry/Cylinder.h"
#include <cmath>

bool Cylinder::intersect(Ray ray, Hit& hit, const f32 tmin, const f32 tmax) const {

    const Vector4 offset = m_center - ray.m_origin;
    const f32 a = ray.m_direction.get_x() * ray.m_direction.get_x() + ray.m_direction.get_y() * ray.m_direction.get_y();
    const f32 b = -2.0f * (offset.get_x() * ray.m_direction.get_x() + offset.get_y() * ray.m_direction.get_y());
    const f32 c = (offset.get_x() * offset.get_x() + offset.get_y() * offset.get_y()) - (m_radius * m_radius);
    const f32 discriminant = b * b - 4.0f * a * c;

    /* if discriminant is less than 0, ray didn't hit object, so do nothing */
    if(discriminant < 0.0f) {
        return false;
    }

    f32 t0 = (-b - sqrtf(discriminant)) / (2 * a);
    f32 t1 = (-b + sqrtf(discriminant)) / (2 * a);

    f32 t_near = static_cast<f32>(fmin(t0, t1));
    f32 t_far = static_cast<f32>(fmax(t0, t1));

    // Intersection with cylinder caps
    f32 t_cap_1 = (m_center.get_z() - ray.m_origin.get_z()) / ray.m_direction.get_z();
    f32 t_cap_2 = (m_center.get_z() + m_height - ray.m_origin.get_z()) / ray.m_direction.get_z();

    f32 t_cap_near = static_cast<f32>(fmin(t_cap_1, t_cap_2));
    f32 t_cap_far = static_cast<f32>(fmax(t_cap_1, t_cap_2));

    // Clamp the intersection range to the near and far clipping planes
    t_near = static_cast<f32>(fmax(t_near, tmin));
    t_cap_far = static_cast<f32>(fmin(t_cap_far, tmax));

    if (t_cap_near > t_far || t_cap_far < 0 || t_cap_far < FLT_EPSILON || t_near > t_cap_far)
        return false;

    f32 t = static_cast<f32>(fmin(t_cap_far, t_near));

    Vector4 capIntersectionPoint;
    capIntersectionPoint = ray.m_origin + t * ray.m_direction;

    f32 axisDistance = 0.0f;
    Vector4 axisIntesectionPoint = m_center + t * m_axis;

    axisDistance = axisDistance + powf(capIntersectionPoint.get_x() - axisIntesectionPoint.get_x(), 2);
    axisDistance = axisDistance + powf(capIntersectionPoint.get_y() - axisIntesectionPoint.get_y(), 2);
    axisDistance = axisDistance + powf(capIntersectionPoint.get_z() - axisIntesectionPoint.get_z(), 2);

    if (axisDistance > m_radius * m_radius) {
        hit.m_Normal.set_x(capIntersectionPoint.get_x() - m_center.get_x());
        hit.m_Normal.set_y(capIntersectionPoint.get_y() - m_center.get_y());
        hit.m_Normal.set_z(0.0f);
    }
    else {
        if(t_cap_far > 0.0f) {
            hit.m_Normal = {0.0f, 0.0f, 1.0f};
        }
        else {
            hit.m_Normal = {0.0f, 0.0f, -1.0f};
        }
    }

    hit.set_t(t_cap_far);
    hit.m_MaterialIndex = m_MaterialIndex;

    // Calculate the point of intersection
    Vector4 intersection_point = ray.m_origin + ray.m_direction * t;
    hit.m_Point = intersection_point.getVec3();

    hit.didHit = true;
    hit.m_Id = m_Id;
    return true;
}


void Cylinder::shift(const Vector4 &offset) {
    /*nothing*/
}