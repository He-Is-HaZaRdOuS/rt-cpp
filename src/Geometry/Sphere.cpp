#include "Geometry/Sphere.h"

void Sphere::intersect(Ray ray, Hit& hit, f32 tmin, f32 tmax) const {
    Vector4 offset = ray.m_origin - m_center;
    f32 a = ray.m_direction.dot(ray.m_direction);
    f32 b = 2.0f * offset.dot(ray.m_direction);
    f32 c = offset.dot(offset) - m_radius * m_radius;
    f32 discriminant = b * b - 4.0f * a * c;

    /* if discriminant is less than 0, ray didn't hit object, so do nothing */
    if(discriminant < 0.0f) {
        return;
    }

    //std::cout << "hit ";
    f32 sqrtd = sqrt(discriminant);
    f32 t0 = (-b - sqrtd) / (2.0f * a);
    f32 t1 = (-b + sqrtd) / (2.0f * a); //unused

    /* if t-distance inside hit is smaller than current hit distance, do nothing */
    /* also discard when hit is outside the frustum ( < near && > far ) */
    if(hit.get_t() < t0 || t0 < tmin || t0 > tmax){
        return;
    }

    hit.set_t(t0);
    hit.set_color((u8*)m_color);

    return;
}