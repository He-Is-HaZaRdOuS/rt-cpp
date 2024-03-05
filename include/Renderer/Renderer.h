#pragma once
#include "Utilities/Macros.h"
#include "Libs/json.h"
#include "Camera/OrthographicCamera.h"
#include "Geometry/Group.h"
#include "Math/Vector4.h"
#include "Renderer/Image.h"
#include <string>
#include <vector>
#include <utility>
#include <fstream>

using json = nlohmann::json;

class Renderer {
public:
    Renderer(u32 width, u32 height) : m_width(width), m_height(height), m_image(width, height){};
    ~Renderer() = default;
    void Render(const std::string& filename, OrthographicCamera& camera, const Group& scene, f32 near, f32 far, bool monochrome);

    u8 m_background_color[3];
private:
    void s_save(const std::string& path);
    u32 s_fragment(f32 x, f32 y, const OrthographicCamera& camera, const Group& scene, bool monochrome);

    Image m_image;
    std::string m_filename;
    u32 m_width;
    u32 m_height;
    f32 m_near;
    f32 m_far;
};