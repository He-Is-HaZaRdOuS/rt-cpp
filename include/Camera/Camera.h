#pragma once
#include "Macros.h"
#include "Beam/Ray.h"

class Camera {
public:
    Camera();
    virtual ~Camera();
    virtual Ray generateRay(f32 x, f32 y) = 0;
};