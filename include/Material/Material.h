#pragma once
#include <Renderer/DirectionalLight.h>

#include "Utilities/Macros.h"
#include "Math/Vector3.h"
#include "Beam/Ray.h"
#include "Beam/Hit.h"
#include "Renderer/Light.h"

class Material {
public:
    virtual ~Material() = default;

    virtual Vector3 shade(const Ray& ray, const Hit& hit, DirectionalLight light) = 0;

    Vector3 m_DiffuseColor;
    Vector3 m_ReflectiveColor;
    Vector3 m_TransparentColor;
    f32 m_IndexOfRefraction;
};
