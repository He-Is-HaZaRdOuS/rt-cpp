#include "Camera/PerspectiveCamera.h"

Ray PerspectiveCamera::generateRay(const f32 x, const f32 y) const {
    Ray r = Ray();

    r.m_origin = m_center;
    r.m_origin.set_w(1);
    r.m_direction.set_x(m_center.get_x() + static_cast<f32>(x - 0.5) * m_scale * m_horizontal.get_x() + static_cast<f32>(y - 0.5) * m_scale * m_up.get_x());
    r.m_direction.set_y(m_center.get_y() + static_cast<f32>(x - 0.5) * m_scale * m_horizontal.get_y() + static_cast<f32>(y - 0.5) * m_scale * m_up.get_y());
    r.m_direction.set_z(m_direction.get_z());
    r.m_direction.set_w(0);
    r.m_direction.normalize();

    return r;
}
