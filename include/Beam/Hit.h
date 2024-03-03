#pragma once
#include "Macros.h"
#include <Math/Vector4.h>

class Hit {
public:
    explicit Hit(f32 t);
    ~Hit() = default;

    [[nodiscard]] f32 get_t() const { return t; }
    Vector4 get_color() { return color; }

private:
    f32 t;
    Vector4 color;

};
