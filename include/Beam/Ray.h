#pragma once
#include "Utilities/Macros.h"
#include <Math/Vector4.h>

class Ray {
public:
    Ray() = default;
    ~Ray() = default;

    Ray(const Vector4& origin, const Vector4& direction) : m_origin(origin), m_direction(direction) {};

    Vector4 m_origin;
    Vector4 m_direction = Vector4::Zero();
};
