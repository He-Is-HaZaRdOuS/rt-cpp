#include "Renderer/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libs/stb_image_write.h"
#include "Geometry/Sphere.h"
#include "Utilities/Timer.h"

void Renderer::Render(const std::string& filename, OrthographicCamera& camera, const Group& scene, f32 near, f32 far, bool monochrome) {
    m_near = near;
    m_far = far;
    m_image.m_data.clear();
    m_image_depth.m_data.clear();
    m_image.init(m_background_color);
    m_image_depth.init(m_background_color);
    Hit hit = Hit();
    for(u32 y = 0; y < m_height; ++y){
        for(u32 x = 0; x < m_width; ++x){
            //TODO
            // USE JUST ONE HIT OBJECT HERE AND PASS IT TO FRAGMENT SHADER
            // INITIALIZE HIT OBJECT TO BACKGROUND COLOR AND FAR PLANE
            // MEASURE PERFORMANCE
            hit.set_t(far);
            s_fragment((f32)x/(f32)m_width, (f32)y/(f32)m_height, x, y, !monochrome, camera, scene, hit);
            hit.set_t(far);
            s_fragment((f32)x/(f32)m_width, (f32)y/(f32)m_height, x, y, monochrome, camera, scene, hit);
        }
    }

        s_save(filename + "_depth.png", monochrome);
        s_save(filename + ".png", !monochrome);
}

void Renderer::s_save(const std::string& path, bool monochrome) {
    /* flip vertically to display uv coordinates correctly */
    stbi_flip_vertically_on_write(true);
    if(monochrome)
        stbi_write_png(path .c_str(), m_width, m_height, 4, m_image_depth.m_data.data(), m_width*4);
    else
        stbi_write_png(path .c_str(), m_width, m_height, 4, m_image.m_data.data(), m_width*4);
}

inline void Renderer::s_fragment(f32 x, f32 y, u32 nx, u32 ny, bool monochrome, const OrthographicCamera& camera, const Group& scene, Hit& hit) {
    Ray ray = camera.generateRay(x, y);
    //Hit hit = Hit();

    /* check for ray intersection with scene objects */
    scene.intersect(ray, hit, m_near, m_far);

    /* if no hit, draw background colors */
    if(hit.get_t() == m_far)
        return;

    /* if monochrome, draw depth data */
    if(monochrome) {
        f32 depth = (m_far - hit.get_t()) / (m_far - m_near);
        m_image_depth.set_pixel(nx, ny, 0xff000000 | ((u32)(depth*255.0) << 16) | ((u32)(depth*255.0) << 8) | (u32)(depth*255.0));
        return;
    }
    /* otherwise draw object's colors */
    else
        m_image.set_pixel(nx, ny, 0xff000000 | (u32(hit.color[2] << 16)) | (u32(hit.color[1] << 8)) | u32(hit.color[0]));
        return;

}

