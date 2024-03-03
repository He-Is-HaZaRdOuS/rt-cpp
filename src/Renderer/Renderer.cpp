#include "Renderer/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libs/stb_image_write.h"
#include "Geometry/Sphere.h"

void Renderer::Render(OrthographicCamera& camera, const Group& scene,  bool monochrome) {
    //TODO
    // Check for monochrome state and render scene accordingly
    // Save output scene as a png and append monochrome state to filename
    for(u32 y = 0; y < m_height; ++y){
        for(u32 x = 0; x < m_width; ++x){
            u32 pixel = s_fragment((f32)x/(f32)m_width, (f32)y/(f32)m_height, camera, scene);
            m_image.m_data.push_back(pixel);
        }
    }

    s_save();
}

void Renderer::s_save() {
    stbi_write_png("output.png", m_width, m_height, 4, m_image.m_data.data(), m_width*4);
}

u32 Renderer::s_fragment(f32 x, f32 y, OrthographicCamera& camera, const Group& scene) {
/*
    x = x * 2.0 - 1.0;
    y = y * 2.0 - 1.0;
    Vector4 rayOrigin = Vector4(0.0, 0.0, 2.0);
    Vector4 rayDirection = Vector4(x, y, -1.0);
    f32 radius = 0.5;

    f32 a = rayDirection.dot(rayDirection);
    f32 b = 2.0 * rayOrigin.dot(rayDirection);
    f32 c = rayOrigin.dot(rayOrigin) - radius * radius;
    f32 d = b * b - 4.0 * a * c;

    if(d >= 0.0)
        return 0xffff00ff;

    return 0xff000000;
    */

    x = x * 2.0 - 1.0;
    y = y * 2.0 - 1.0;
    Ray ray = camera.generateRay(x, y);
    std::shared_ptr<Object3D> sphere = scene.objects.at(0);

    f32 a = ray.m_direction.dot(ray.m_direction);
    f32 b = 2.0 * ray.m_origin.dot(ray.m_direction);
    f32 c = ray.m_origin.dot(ray.m_origin) - dynamic_cast<Sphere*>(sphere.get())->m_radius * dynamic_cast<Sphere*>(sphere.get())->m_radius;
    f32 d = b * b - 4.0 * a * c;

    if(d >= 0.0)
        return 0xff000000 | (i32(sphere->m_color[2]*255.0) << 16) | (i32(sphere->m_color[1]*255.0) << 8) | (i32(sphere->m_color[2]*255.0));

    return 0xff000000;

}

