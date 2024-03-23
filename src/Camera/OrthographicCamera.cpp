#include "Camera/OrthographicCamera.h"

Ray OrthographicCamera::generateRay(const f32 x, const f32 y) const {
    Ray r = Ray();

    r.m_origin = (m_center + static_cast<f32>(x - 0.5) * static_cast<f32>(m_size) * m_horizontal + static_cast<f32>(y - 0.5) * static_cast<f32>(m_size) * m_up);
    r.m_origin.set_w(1);
    r.m_direction = m_direction;
    r.m_direction.set_w(0);
    r.m_direction.normalize();

    return r;
}
