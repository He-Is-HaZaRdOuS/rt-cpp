#include "Renderer/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libs/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Libs/stb_image_write.h"

void Renderer::Render(const OrthographicCamera& camera, const Group& scene,  bool monochrome) {
    //TODO
    // Check for monochrome state and render scene accordingly
    // Save output scene as a png and append monochrome state to filename
    for(i32 y = m_height - 1; y >=  0; --y){
        for(u32 x = 0; x < m_width; ++x){
            u32 pixel = s_fragment((f32)x/(f32)m_width, (f32)y/(f32)m_height);
            m_image.m_data.push_back(pixel);
        }
    }

    s_save();
}

void Renderer::s_save() {
    stbi_write_png("output.png", m_width, m_height, 4, m_image.m_data.data(), m_width*4);
}

u32 Renderer::s_fragment(f32 x, f32 y) {
    u8 r = (u8)(x*255.0);
    u8 g = (u8)(y*255.0);
    return 0xff000000 | (g << 8) | r;
}

