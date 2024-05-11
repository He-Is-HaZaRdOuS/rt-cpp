#pragma once
#include "Utilities/Macros.h"
#include "Libs/json.h"
#include "Camera/OrthographicCamera.h"
#include "Camera/PerspectiveCamera.h"
#include "Geometry/Group.h"
#include "Math/Vector4.h"
#include "Renderer/Image.h"
#include "Renderer/Light.h"
#include "Renderer/DirectionalLight.h"
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <Material/PhongMaterial.h>

using json = nlohmann::json;

class Renderer {
public:
    Renderer(const u32 width, const u32 height) : m_Image(width, height), m_ImageDepth(width, height), m_Width(width), m_Height(height), m_Near(0),
                                                  m_Far(0) {
    };
    ~Renderer() = default;
    void Render(const std::string& filename, const std::shared_ptr<Camera>& camera, f32 near, f32 far, bool monochrome);

    static Vector3 s_BackgroundColor;
    static Vector3 s_AmbientColor;
    static Vector3 s_GlobalColor;
    static Group s_scene;
    static std::vector<DirectionalLight> s_lights;
    static std::vector<PhongMaterial> s_materials;
private:
    void s_save(const std::string& path, bool monochrome) const;
    inline void s_fragment(f32 x, f32 y, u32 nx, u32 ny, bool monochrome, const std::shared_ptr<Camera>& camera, Hit hit);
    inline Vector3 traceRay(Ray &ray, f32 tmin, u32 bounces, f32 weight, f32 indexOfRefraction, Hit &hit);

    Image m_Image;
    Image m_ImageDepth;
    std::string m_Filename;
    u32 m_Width;
    u32 m_Height;
    f32 m_Near;
    f32 m_Far;
};