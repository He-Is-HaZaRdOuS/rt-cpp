#pragma once
#include <Renderer/DirectionalLight.h>

#include "Utilities/Macros.h"
#include "Material/Material.h"
#include "Beam/Hit.h"
#include "Math/Vector3.h"

class PhongMaterial : virtual public Material {
public:
    PhongMaterial() = default;
    ~PhongMaterial() override = default;

    Vector3 shade(const Ray& ray, const Hit& hit, DirectionalLight light) override ;

    Vector3 m_SpecularColor{};
    f32 m_ExponentValue{};
    bool m_IsReflective = false;
    bool m_IsTransparent = false;
};
