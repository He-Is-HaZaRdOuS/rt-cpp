#pragma once
#include "Utilities/Macros.h"
#include "Camera/Camera.h"
#include "Beam/Ray.h"
#include "Math/Vector4.h"
#include <iostream>
#include <cmath>

class PerspectiveCamera : virtual public Camera {
public:

    PerspectiveCamera() = default;
    PerspectiveCamera(const f32 angle, const Vector4& center, const Vector4& direction, const Vector4& up) : m_angle(angle), m_center(center), m_direction(direction), m_up(up), m_horizontal(m_direction.cross_zero(m_up)){
        /* calculate scale factor */
    };
    ~PerspectiveCamera() override = default;

    [[nodiscard]] Ray generateRay(f32 x, f32 y) const override;
    [[nodiscard]] Ray generateSampledRay(f32 x, f32 y, f32 u, f32 v) const override;
    [[nodiscard]] Vector4 getDirection() const override { return m_direction; };
    [[nodiscard]] Vector4 getPosition() const override { return m_center; };

    f32 m_scale{};
    f32 m_angle{};
    Vector4 m_center;
    Vector4 m_direction = Vector4::Zero();
    Vector4 m_up = Vector4::Zero();
    Vector4 m_horizontal;

};
