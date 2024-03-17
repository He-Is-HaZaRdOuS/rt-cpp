#pragma once
#include "Utilities/Macros.h"
#include "Math/Vector3.h"

class Light {
public:
    Light() = default;
    ~Light() = default;

    Vector3 m_direction;
    Vector3 m_color;
};
