#include "Material/PhongMaterial.h"

#include <cmath>
#include <Renderer/DirectionalLight.h>
#include <Renderer/Renderer.h>

inline Vector3 reflect(const Vector3& I, const Vector3& N) {
    return N * 2 * I.dot(N) - I;
}

Vector3 PhongMaterial::shade(const Ray &ray, const Hit &hit, DirectionalLight light) {
    Vector4 camSource = ray.m_direction;
    //camSource.normalize();
    light.m_Direction.normalize();

    Vector4 reflectSource = reflect(light.m_Direction, hit.m_Normal);
    reflectSource.normalize();
    f32 specularStrength = std::max(camSource.dot(reflectSource), static_cast<f32>(0.0));
    f32 specularE = powf(specularStrength, m_ExponentValue);

    const Vector3 ambientK = Renderer::s_AmbientColor * m_DiffuseColor;
    const Vector3 diffuseK = std::max(hit.m_Normal.dot(-light.m_Direction), static_cast<f32>(0.0)) * (m_DiffuseColor * light.m_Color);

    Vector3 specularK = specularE *  (m_SpecularColor * light.m_Color);
    /* remove components when debugging */
    Vector3 pixelColor = (ambientK + diffuseK + specularK);
    //std::cout << "Light: " << light.m_Direction << "Normal: " << hit.m_Normal << "Reflect: " << reflectSource << "\n";
    //std::cout << reflectSource << std::endl;
    return pixelColor;
}
