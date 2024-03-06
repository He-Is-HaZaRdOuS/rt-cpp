#pragma once
#include "Utilities/Macros.h"
#include <vector>

class Image {
public:
    Image(u32 width, u32 height);
    ~Image() = default;

    void init(const u8 base_color[]);
    void set_pixel(u32 x, u32 y, u32 color);
    u32 get_pixel(u32 x, u32 y);

    u32 m_width;
    u32 m_height;
    std::vector<u32> m_data;

};
