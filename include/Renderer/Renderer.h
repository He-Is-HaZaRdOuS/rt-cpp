#pragma once
#include "Macros.h"
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
    Renderer(std::string path, u32 width, u32 height, u32 near, u32 far) : m_filename(path), m_width(width), m_height(height), m_near(near), m_far(far),
                                                                           m_image(width, height){};
    ~Renderer() = default;
    void Render(OrthographicCamera& camera, const Group& scene, bool monochrome);

    f32 m_background_color[3];
private:
    void s_save();
    u32 s_fragment(f32 x, f32 y, OrthographicCamera& camera, const Group& scene);

    Image m_image;
    std::string m_filename;
    u32 m_width;
    u32 m_height;
    u32 m_near;
    u32 m_far;
};