#pragma once
#include "Utilities/Macros.h"
#include <Math/Vector4.h>
#include <cfloat>
#include <cstring>

class Hit {
public:
    Hit() = default;
    ~Hit() = default;

    [[nodiscard]] f32 get_t() const { return t; }
    u8* get_color() { return color; }
    void set_t(f32 newDistance) { this->t = newDistance; }
    void set_color(u8 newColor[]) { memcpy(this->color, newColor, sizeof(this->color)); }
    f32 t{FLT_MAX};
    u8 color[3]{0,0,0};
private:


};
