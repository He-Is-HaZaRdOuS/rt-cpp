#include <iostream>
#include "Camera/OrthographicCamera.h"

Ray OrthographicCamera::generateRay(f32 x, f32 y) {
    Ray r = Ray();

    r.m_origin.set_x(m_center.get_x() + (x - 0.5) * m_size * m_horizontal.get_x() + (y - 0.5) * m_size * m_up.get_x());
    r.m_origin.set_y(m_center.get_y() + (x - 0.5) * m_size * m_horizontal.get_y() + (y - 0.5) * m_size * m_up.get_y());
    r.m_origin.set_z(m_center.get_z() + (x - 0.5) * m_size * m_horizontal.get_z() + (y - 0.5) * m_size * m_up.get_z());
    r.m_direction = m_direction;
    r.m_direction.normalize();

    return r;
}
