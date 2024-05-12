#pragma once
#include "Utilities/Macros.h"
#include "Math/Vector3.h"
#include "Renderer/Light.h"

class DirectionalLight : virtual public Light{
public:
    DirectionalLight() = default;
    ~DirectionalLight() override = default;

    Vector3 m_Direction;
};
