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
    for(u32 y = 0; y < m_height; ++y){
        for(u32 x = 0; x < m_width; ++x){
            u32 pixel = s_fragment((f32)x/(f32)m_width, (f32)y/(f32)m_height, camera, scene, monochrome);
            m_image.m_data.push_back(pixel);
        }
    }

    if(monochrome)
        s_save(filename + "_depth.png");
    else
        s_save(filename + ".png");
}

void Renderer::s_save(const std::string& path) {
    /* flip vertically to display uv coordinates correctly */
    stbi_flip_vertically_on_write(true);
    stbi_write_png(path .c_str(), m_width, m_height, 4, m_image.m_data.data(), m_width*4);
}

u32 Renderer::s_fragment(f32 x, f32 y, const OrthographicCamera& camera, const Group& scene, bool monochrome) {
    Ray ray = camera.generateRay(x, y);
    Hit hit = Hit();

    /* check for ray intersection with scene objects */
    scene.intersect(ray, hit, m_near, m_far);

    /* if no hit, draw background colors */
    if(hit.get_t() == FLT_MAX)
        return 0xff000000 | ((u32)(m_background_color[2]) << 16) | ((u32)(m_background_color[1]) << 8) | (u32)(m_background_color[0]);

    /* if monochrome, draw depth data */
    if(monochrome) {
        f32 depth = (m_far - hit.get_t()) / (m_far - m_near);
        return 0xff000000 | ((u32)(depth*255.0) << 16) | ((u32)(depth*255.0) << 8) | (u32)(depth*255.0);
    }
    /* otherwise draw object's colors */
    else
        return 0xff000000 | (u32(hit.color[2] << 16)) | (u32(hit.color[1] << 8)) | u32(hit.color[0]);

}

