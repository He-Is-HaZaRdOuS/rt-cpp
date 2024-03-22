#include "Geometry/Sphere.h"

bool Sphere::intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const {
    Vector4 offset = ray.m_origin - m_center;
    f32 a = ray.m_direction.dot(ray.m_direction);
    f32 b = 2.0f * offset.dot(ray.m_direction);
    f32 c = offset.dot(offset) - m_radius * m_radius;
    f32 discriminant = b * b - 4.0f * a * c;

    /* if discriminant is less than 0, ray didn't hit object, so do nothing */
    if(discriminant < 0.0f) {
        return false;
    }

    //TODO
    // CHECK IF EITHER T0 OR T1 ARE NEGATIVE AND USE THE POSITIVE ONE
    // MEASURE THE RESULTS
    //std::cout << "hit ";
    f32 sqrtd = (f32) sqrt(discriminant);
    f32 t0 = (-b - sqrtd) / (2.0f * a);
    f32 t1 = (-b + sqrtd) / (2.0f * a);
    f32 t;


    if(t0 > 0 && t1 > 0) {
        t = (t0 > t1) ? t1 : t0;
    }
    else if(t0 < 0 && t1 > 0)
        t = t1;
    else if(t1 < 0 && t0 > 0)
        t = t0;
    else
        return false;


    /* if t-distance inside hit is smaller than current hit distance, do nothing */
    /* also discard when hit is outside the frustum ( < near && > far ) */
    if(hit.get_t() < t || t < tmin || t > tmax){
        return false;
    }

    hit.set_t(t);
    hit.set_color(m_color);
    hit.set_normal((ray.m_origin + ray.m_direction * t) - m_center);
    hit.m_normal.normalize();
    return true;
}