#pragma once
#include "Utilities/Macros.h"
#include "Beam/Ray.h"

class Camera {
public:
    virtual ~Camera()= default;
    [[nodiscard]] virtual Ray generateRay(f32 x, f32 y) const = 0;
};