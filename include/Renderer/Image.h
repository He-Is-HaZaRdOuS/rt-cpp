#pragma once
#include "Utilities/Macros.h"
#include <vector>

class Image {
public:
    Image(u32 width, u32 height);
    ~Image() = default;

    std::vector<u32> m_data;

};
