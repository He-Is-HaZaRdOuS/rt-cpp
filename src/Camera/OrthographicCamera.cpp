#include "Camera/OrthographicCamera.h"

Ray OrthographicCamera::generateRay(f32 x, f32 y) const {
    Ray r = Ray();

    r.m_origin = (m_center + (f32)(x - 0.5) * (f32)m_size * m_horizontal + (f32)(y - 0.5) * (f32)m_size * m_up);
    r.m_direction = m_direction;
    r.m_direction.normalize();

    return r;
}
