#include "Renderer/Image.h"

Image::Image(u32 width, u32 height) {
    m_data.reserve(width * height);
}