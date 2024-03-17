#include "Renderer/Image.h"

Image::Image(u32 width, u32 height) {
    m_width = width;
    m_height = height;
}

void Image::init(const f32 base_color[]) {
    m_data.reserve(m_width * m_height);
    u32 size = m_width * m_height;
    u32 color = 0xff000000;
    color |= ((u32(base_color[2]*255) << 16)) | ((u32(base_color[1]*255) << 8)) | u32(base_color[0]*255);
    for(u32 i = 0; i < size; ++i)
        m_data.emplace_back(color);
}

void Image::set_pixel(u32 x, u32 y, u32 color) {
    m_data.at(x + y * m_height) = color;
}

u32 Image::get_pixel(u32 x, u32 y) {
    return m_data.at(x + y * m_height);
}
