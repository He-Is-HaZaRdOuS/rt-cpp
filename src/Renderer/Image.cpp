#include "Renderer/Image.h"

Image::Image(const u32 width, const u32 height) {
    m_width = width;
    m_height = height;
}

void Image::init(const Vector3& base_color) {
    m_data.reserve(m_width * m_height);
    const u32 size = m_width * m_height;
    u32 color = 0xff000000;
    color |= ((static_cast<u32>(base_color.get_b() * 255) << 16)) | ((static_cast<u32>(base_color.get_g() * 255) << 8)) | static_cast<u32>(base_color.get_r() * 255);
    for(u32 i = 0; i < size; ++i)
        m_data.emplace_back(color);
}

void Image::set_pixel(const u32 x, const u32 y, const u32 color) {
    m_data.at(x + y * m_height) = color;
}

u32 Image::get_pixel(const u32 x, const u32 y) const {
    return m_data.at(x + y * m_height);
}
