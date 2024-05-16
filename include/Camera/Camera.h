#pragma once
#include "Utilities/Macros.h"
#include "Beam/Ray.h"
#include "Math/Vector3.h"

class Camera {
public:
    virtual ~Camera()= default;
    [[nodiscard]] virtual Ray generateRay(f32 x, f32 y) const = 0;
    [[nodiscard]] virtual Ray generateSampledRay(f32 x, f32 y, f32 u, f32 v) const = 0;
    [[nodiscard]] virtual Vector4 getDirection() const = 0;
    [[nodiscard]] virtual Vector4 getPosition() const = 0;
};