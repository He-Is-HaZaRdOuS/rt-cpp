#include "Camera/PerspectiveCamera.h"

Ray PerspectiveCamera::generateRay(const f32 x, const f32 y) const {
    Ray r = Ray();

    r.m_origin = m_center;
    r.m_origin.set_w(1);
    r.m_direction = (m_direction * m_scale) + (m_up * ((y - 0.5f) * 2.0f)) + (m_horizontal * ((x - 0.5f) * 2.0f));
    r.m_direction.set_w(0);
    r.m_direction.normalize();

    return r;
}
