#pragma once
#include "Utilities/Macros.h"
#include "Math/Vector3.h"

class Light {
public:
    virtual ~Light() = default;

    Vector3 m_Color;
};
