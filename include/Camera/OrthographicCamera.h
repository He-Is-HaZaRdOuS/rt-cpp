#pragma once
#include "Utilities/Macros.h"
#include "Camera/Camera.h"
#include "Beam/Ray.h"
#include "Math/Vector4.h"
#include <iostream>

class OrthographicCamera : virtual public Camera {
public:

    OrthographicCamera() = default;
    OrthographicCamera(const f32 size, const Vector4& center, const Vector4& direction, const Vector4& up) : m_size(size), m_center(center), m_direction(direction), m_up(up){
        /*do nothing*/
    };
    ~OrthographicCamera() override = default;

    [[nodiscard]] Ray generateRay(f32 x, f32 y) const override;
    [[nodiscard]] Ray generateSampledRay(f32 x, f32 y, f32 u, f32 v) const override;
    [[nodiscard]] Vector4 getDirection() const override { return m_direction; };
    [[nodiscard]] Vector4 getPosition() const override { return m_center; };

    f32 m_size{};
    Vector4 m_center;
    Vector4 m_direction = Vector4::Zero();
    Vector4 m_up = Vector4::Zero();
    Vector4 m_horizontal;
};
