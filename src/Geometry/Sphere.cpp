#include "Geometry/Sphere.h"

#include <cmath>

bool Sphere::intersect(Ray &ray, Hit& hit, const f32 tmin, const f32 tmax) const {

    const Vector4 offset = m_center - ray.m_origin;
    const f32 a = ray.m_direction.dot(ray.m_direction);
    const f32 b = -2.0f * offset.dot(ray.m_direction);
    const f32 c = offset.dot(offset) - (m_radius * m_radius);
    const f32 discriminant = b * b - 4.0f * a * c;

    /* if discriminant is less than 0, ray didn't hit object, so do nothing */
    if(discriminant < 0.0f) {
        //std::cout << "no";
        return false;
    }

    //TODO
    // CHECK IF EITHER T0 OR T1 ARE NEGATIVE AND USE THE POSITIVE ONE
    // MEASURE THE RESULTS
    //std::cout << "hit ";
    const f32 sqrtd = static_cast<f32>(sqrt(discriminant));
    const f32 t0 = (-b - sqrtd) / (2.0f * a);
    const f32 t1 = (-b + sqrtd) / (2.0f * a);
    f32 t;


    if(t0 > 0 && t1 > 0) {
        t = (t0 < t1) ? t0 : t1;
    }
    else if(t0 < 0 && t1 > 0)
        t = t1;
    else if(t1 < 0 && t0 > 0)
        t = t0;

    /* if t-distance inside hit is smaller than current hit distance, do nothing */
    /* also discard when hit is outside the frustum ( < near && > far ) */
    if(hit.get_t() < t || t < tmin || t > tmax){
        return false;
    }

    hit.set_t(t);

    // set hit material index to sphere material index
    hit.m_MaterialIndex = m_MaterialIndex;

    // Calculate the point of intersection
    Vector4 intersection_point = ray.m_origin + ray.m_direction * t;
    hit.m_Point = intersection_point.getVec3();
    //hit.m_Point.normalize();

    // Calculate the hit normal
    Vector4 hit_normal = (intersection_point - m_center) * (1/m_radius);

    //hit_normal = hit_normal * 0.5 + 0.5;

    // Set the hit normal
    hit.set_normal(hit_normal);
    hit.didHit = true;
    hit.m_Id = m_Id;
    hit.m_OutwardNormal = ray.m_direction.dot(hit.m_Normal) < 0;
    return true;
}
