#pragma once
#include "Utilities/Macros.h"
#include "Libs/json.h"
#include "Camera/OrthographicCamera.h"
#include "Camera/PerspectiveCamera.h"
#include "Geometry/Group.h"
#include "Math/Vector4.h"
#include "Renderer/Image.h"
#include "Renderer/Light.h"
#include <string>
#include <vector>
#include <utility>
#include <fstream>

using json = nlohmann::json;

class Renderer {
public:
    Renderer(const u32 width, const u32 height) : m_image(width, height), m_image_depth(width, height), m_width(width), m_height(height), m_near(0),
                                                  m_far(0) {
    };
    ~Renderer() = default;
    void Render(const std::string& filename, const std::shared_ptr<Camera>& camera, const Group& scene, Light& light, f32 near, f32 far, bool monochrome);

    Vector3 m_background_color;
    Vector3 m_ambient_color;
    Vector3 m_global_color;
private:
    void s_save(const std::string& path, bool monochrome) const;
    inline void s_fragment(f32 x, f32 y, u32 nx, u32 ny, bool monochrome, const std::shared_ptr<Camera>& camera, const Group& scene, const Light &light, Hit& hit);

    Image m_image;
    Image m_image_depth;
    std::string m_filename;
    u32 m_width;
    u32 m_height;
    f32 m_near;
    f32 m_far;
};