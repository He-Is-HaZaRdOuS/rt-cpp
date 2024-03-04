#pragma once
#include "Macros.h"
#include "Camera/Camera.h"
#include "Beam/Ray.h"
#include "Math/Vector4.h"
#include <iostream>

class OrthographicCamera : public Camera {
public:

    OrthographicCamera(const u32 size, const Vector4& center, const Vector4& direction, const Vector4& up) : m_size(size), m_center(center), m_direction(direction), m_up(up), m_horizontal(m_direction.cross_zero(m_up)){
        m_horizontal = direction.cross(up);
        std::cout << m_direction;
        std::cout << m_up;
        std::cout << m_horizontal;
    };
    ~OrthographicCamera(){/*nothing*/};

    Ray generateRay(f32 x, f32 y) override;

    u32 m_size{};
    Vector4 m_center;
    Vector4 m_direction = Vector4::Zero();
    Vector4 m_up = Vector4::Zero();
    Vector4 m_horizontal;
};