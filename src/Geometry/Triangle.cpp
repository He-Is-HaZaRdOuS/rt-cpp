#include "Geometry/Triangle.h"

bool Triangle::intersect(Ray ray, Hit &hit, f32 tmin, f32 tmax) const {
// compute the plane's normal
    Vector4 v0v1 = m_v2 - m_v1;
    Vector4 v0v2 = m_v3 - m_v1;
    // no need to normalize
    Vector4 N = v0v1.cross_zero(v0v2); // N
    f32 denom = N.dot(N);

    // Step 1: finding P

    // check if the ray and plane are parallel.
    f32 NdotRayDirection = N.dot(ray.m_direction);
    //TODO
    // CHECK FOR EPSILON INACCURACIES

    if (fabs(NdotRayDirection) < FLT_EPSILON) // almost 0
        return false; // they are parallel so they don't intersect!

    // compute d parameter using equation 2
    f32 d = -N.dot(m_v1);

    // compute t (equation 3)
    f32 t = -(N.dot(ray.m_origin) + d) / NdotRayDirection;
    // check if the triangle is behind the ray
    if (t < 0) return false; // the triangle is behind

    // compute the intersection point using equation 1
    Vector4 P = ray.m_origin + t * ray.m_direction;

    // Step 2: inside-outside test
    Vector4 C; // vector perpendicular to triangle's plane

    // edge 0
    Vector4 edge0 = m_v2 - m_v1;
    Vector4 vp0 = P - m_v1;
    C = edge0.cross_zero(vp0);
    if (N.dot(C) < 0) return false; // P is on the right side

    // edge 1
    Vector4 edge1 = m_v3 - m_v2;
    Vector4 vp1 = P - m_v2;
    C = edge1.cross_zero(vp1);
    if ((N.dot(C)) < 0)  return false; // P is on the right side

    // edge 2
    Vector4 edge2 = m_v1 - m_v3;
    Vector4 vp2 = P - m_v3;
    C = edge2.cross_zero(vp2);
    if ((N.dot(C)) < 0) return false; // P is on the right side;

    /* if t-distance inside hit is smaller than current hit distance, do nothing */
    /* also discard when hit is outside the frustum ( < near && > far ) */
    if(hit.get_t() < t || t < tmin || t > tmax){
        return false;
    }

    hit.set_t(t);
    hit.set_color(m_color);
    hit.set_normal(m_normal);
    hit.m_normal.normalize();
    return true; // this ray hits the triangle
}
