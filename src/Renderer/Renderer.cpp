#include "Renderer/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libs/stb_image_write.h"
#include "Geometry/Sphere.h"
#include "Utilities/Timer.h"
#include <cmath>

inline u32 ConvertToRGBA(const Vector3& v) {
    const u8 r = v.get_r() * 255;
    const u8 g = v.get_g() * 255;
    const u8 b = v.get_b() * 255;
    const u32 result = 0xff000000 | b << 16 | g << 8 | r;
    return result;
}

inline u32 ConvertToRGBA(const Vector4& v) {
    const u8 r = v.get_r() * 255;
    const u8 g = v.get_g() * 255;
    const u8 b = v.get_b() * 255;
    const u8 a = v.get_a() * 255;
    const u32 result = 0xff000000 | b << 16 | g << 8 | r;
    return result;
}

void Renderer::Render(const std::string& filename, const std::shared_ptr<Camera>& camera, const Group& scene, Light& light, f32 near, f32 far, bool monochrome) {
    m_near = near;
    m_far = far;
    m_image.m_data.clear();
    m_image_depth.m_data.clear();
    m_image.init(m_background_color);
    m_image_depth.init(m_background_color);
    m_global_color = m_background_color * m_ambient_color;
    light.m_direction.normalize();
    Timer timer;

    #pragma omp parallel for collapse(2)
    for(u32 y = 0; y < m_height; ++y){
        for(u32 x = 0; x < m_width; ++x){
            /* create thread-specific hit object */
            thread_local Hit hit = Hit();
            hit.set_t(far);
            s_fragment(static_cast<f32>(x)/static_cast<f32>(m_width), static_cast<f32>(y)/static_cast<f32>(m_height), x, y, !monochrome, camera, scene, light, hit);
            //hit.set_t(far);
            //s_fragment((f32)x/(f32)m_width, (f32)y/(f32)m_height, x, y, monochrome, camera, scene, light, hit);
        }
    }
    timer.Stop();
    //s_save(filename + "_depth.png", monochrome);
    s_save(filename + ".png", !monochrome);
}

void Renderer::s_save(const std::string& path, bool monochrome) const {
    /* flip vertically to display uv coordinates correctly */
    stbi_flip_vertically_on_write(true);
    //if(monochrome)
    //    stbi_write_png(path .c_str(), m_width, m_height, 4, m_image_depth.m_data.data(), m_width*4);
    //else
        stbi_write_png(path .c_str(), static_cast<i32>(m_width), static_cast<i32>(m_height), 4, m_image.m_data.data(), static_cast<i32>(m_width) * 4);
}

inline void Renderer::s_fragment(const f32 x, const f32 y, const u32 nx, const u32 ny, bool monochrome, const std::shared_ptr<Camera>& camera, const Group& scene, const Light& light, Hit& hit) {
    const Ray ray = camera->generateRay(x, y);

    /* check for ray intersection with scene m_objects */
    scene.intersect(ray, hit, m_near, m_far);

    /* normalize surface normal vector */
    hit.m_normal.normalize();

    const f32 diffuseK = std::max(hit.m_normal.dot(-light.m_direction), static_cast<f32>(0.0));

    const Vector3 pixelColor = m_ambient_color * hit.m_color + diffuseK * (hit.m_color * light.m_color);

    /* if no hit, draw background colors */
    if(hit.get_t() == m_far) {
        //m_image_depth.set_pixel(nx, ny, ConvertToRGBA(bg));
        m_image.set_pixel(nx, ny, ConvertToRGBA(m_global_color));
        return;
    }

    /* if monochrome, draw depth data */
    /*
    if (monochrome) {
        f32 depth = (m_far - hit.get_t()) / (m_far - m_near);
        m_image_depth.set_pixel(nx, ny, ConvertToRGBA(Vector3(depth, depth, depth)));
        return;
    }
    */

    /* otherwise draw object's colors */
    m_image.set_pixel(nx, ny, ConvertToRGBA(pixelColor));
}
