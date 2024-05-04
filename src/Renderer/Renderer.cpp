#include "Renderer/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libs/stb_image_write.h"
#include "Geometry/Sphere.h"
#include "Utilities/Timer.h"
#include "PinnedVector.h"
#include <cmath>
#include <Material/PhongMaterial.h>

Vector3 Renderer::s_BackgroundColor;
Vector3 Renderer::s_AmbientColor;
Vector3 Renderer::s_GlobalColor;
Group Renderer::s_scene;
std::vector<DirectionalLight> Renderer::s_lights;
std::vector<PhongMaterial> Renderer::s_materials;

/*Java-like instanceof function (Thanks stackoverflow.com)*/
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

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

void Renderer::Render(const std::string& filename, const std::shared_ptr<Camera>& camera, f32 near, f32 far, bool monochrome) {
    m_Near = near;
    m_Far = far;
    m_Image.m_data.clear();
    m_ImageDepth.m_data.clear();
    m_Image.init(Renderer::s_BackgroundColor);
    m_ImageDepth.init(Renderer::s_BackgroundColor);
    Timer timer;

    //#pragma omp parallel for collapse(2)
    for(u32 y = 0; y < m_Height; ++y){
        for(u32 x = 0; x < m_Width; ++x){
            /* create thread-specific hit object */
            thread_local Hit hit = Hit();
            hit.set_t(far);
            s_fragment(static_cast<f32>(x)/static_cast<f32>(m_Width), static_cast<f32>(y)/static_cast<f32>(m_Height), x, y, !monochrome, camera, hit);
            //hit.set_t(far);
            //s_fragment((f32)x/(f32)m_Width, (f32)y/(f32)m_Height, x, y, monochrome, camera, scene, light, hit);
        }
    }
    timer.Stop();
    //s_save(filename + "_depth.png", monochrome);
    s_save(filename + ".png", !monochrome);
}

void Renderer::s_save(const std::string& path, bool monochrome) const {
    /* flip vertically to display uv coordinates correctly */
    stbi_flip_vertically_on_write(true);
    stbi_write_png(path .c_str(), static_cast<i32>(m_Width), static_cast<i32>(m_Height), 4, m_Image.m_data.data(), static_cast<i32>(m_Width) * 4);
    /*
    if(monochrome) {
        stbi_write_png(path .c_str(), m_Width, m_Height, 4, s_ImageDepth.m_data.data(), m_Width*4);
    }
    else {
        stbi_write_png(path .c_str(), static_cast<i32>(m_Width), static_cast<i32>(m_Height), 4, s_Image.m_data.data(), static_cast<i32>(m_Width) * 4);
    }
    */
}

inline void Renderer::s_fragment(const f32 x, const f32 y, const u32 nx, const u32 ny, bool monochrome, const std::shared_ptr<Camera>& camera, Hit& hit) {
    Ray ray = camera->generateRay(x, y);

    Vector3 pixelColor = traceRay(ray, m_Near, 5, 1.0,1.0, hit);

    /* if no hit, draw background colors */
    if(hit.get_t() == m_Far) {
        //s_ImageDepth.set_pixel(nx, ny, ConvertToRGBA(bg));
        m_Image.set_pixel(nx, ny, ConvertToRGBA(s_GlobalColor));
        return;
    }

    /* otherwise draw object's colors */
    m_Image.set_pixel(nx, ny, ConvertToRGBA(pixelColor));

    /* if monochrome, draw depth data */
    /*
    if (monochrome) {
        f32 depth = (s_Far - hit.get_t()) / (s_Far - s_Near);
        s_ImageDepth.set_pixel(nx, ny, ConvertToRGBA(Vector3(depth, depth, depth)));
        return;
    }
    */

}

Vector3 Renderer::traceRay(Ray &ray, f32 tmin, u32 bounces, f32 weight, f32 indexOfRefraction, Hit &hit) {

    /* check for ray intersection with scene m_objects */
    s_scene.intersect(ray, hit, m_Near, m_Far);

    /* normalize surface normal vector */
    hit.m_Normal.normalize();

    PhongMaterial material = Renderer::s_materials.at(hit.m_MaterialIndex);

    Vector3 rgb = {0.0, 0.0, 0.0};
    for(auto& light : Renderer::s_lights) {
        light.m_Direction.normalize();
        //std::cout << light.m_Direction;
        //std::cout << light.m_Color;
        Ray subRay = Ray(hit.m_Point, -light.m_Direction);
        Hit subHit = Hit();
        bool isInShadow = s_scene.inShadow(subRay, subHit, 0.0001, m_Far);
        if(!isInShadow) {
            rgb = rgb + material.shade(ray, hit, light);
        }
        else {
            std::cout << "shaded";
        }
    }
    return rgb;
}
