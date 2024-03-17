#include "Renderer/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libs/stb_image_write.h"
#include "Geometry/Sphere.h"
#include "Utilities/Timer.h"

#include <cmath>

inline u32 ConvertToRGBA(const Vector3& v) {
    u8 r = v.get_r() * 255;
    u8 g = v.get_g() * 255;
    u8 b = v.get_b() * 255;
    u32 result = 0xff000000 | b << 16 | g << 8 | r;
    return result;
}

inline u32 ConvertToRGBA(const Vector4& v) {
    u8 r = v.get_r() * 255;
    u8 g = v.get_g() * 255;
    u8 b = v.get_b() * 255;
    u8 a = v.get_a() * 255;
    u32 result = 0xff000000 | b << 16 | g << 8 | r;
    return result;
}

void Renderer::Render(const std::string& filename, const std::shared_ptr<Camera>& camera, const Group& scene, Light& light, f32 near, f32 far, bool monochrome) {
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
            s_fragment((f32)x/(f32)m_width, (f32)y/(f32)m_height, x, y, !monochrome, camera, scene, light, hit);
            //hit.set_t(far);
            //s_fragment((f32)x/(f32)m_width, (f32)y/(f32)m_height, x, y, monochrome, camera, scene, light, hit);
        }
    }

        //s_save(filename + "_depth.png", monochrome);
        s_save(filename + ".png", !monochrome);
}

void Renderer::s_save(const std::string& path, bool monochrome) {
    /* flip vertically to display uv coordinates correctly */
    stbi_flip_vertically_on_write(true);
    //if(monochrome)
     //   stbi_write_png(path .c_str(), m_width, m_height, 4, m_image_depth.m_data.data(), m_width*4);
    //else
        stbi_write_png(path .c_str(), m_width, m_height, 4, m_image.m_data.data(), m_width*4);
}

inline void Renderer::s_fragment(f32 x, f32 y, u32 nx, u32 ny, bool monochrome, const std::shared_ptr<Camera>& camera, const Group& scene, Light& light, Hit& hit) {
    Ray ray = camera->generateRay(x, y);
    //Hit hit = Hit();

    /* check for ray intersection with scene objects */
    scene.intersect(ray, hit, m_near, m_far);

    // Normalize light direction and surface normal vectors
    light.m_direction.normalize();
    hit.m_normal.normalize();

// Calculate diffuse component
    f32 diffuseC = std::max((f32)(hit.m_normal.dot(-light.m_direction)), (f32)0.0);

// Calculate ambient component
    Vector3 ambientColor(m_ambient_color[0], m_ambient_color[1], m_ambient_color[2]);

// Compute final pixel color
    Vector3 pixelColor = ambientColor + light.m_color * diffuseC;


    /* if no hit, draw background colors */
    if(hit.get_t() == m_far) {
        Vector3 bg = Vector3(m_background_color[0], m_background_color[1], m_background_color[2]);
        //m_image_depth.set_pixel(nx, ny, ConvertToRGBA(bg));
        m_image.set_pixel(nx, ny, ConvertToRGBA(bg * ambientColor));
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
    //m_image.set_pixel(nx, ny, ConvertToRGBA(hit.getColor()));


// Set the pixel color in the image
    m_image.set_pixel(nx, ny, ConvertToRGBA(pixelColor * hit.m_color));
}
