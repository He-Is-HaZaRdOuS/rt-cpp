#pragma once
#include "Utilities/Macros.h"

static u32 PCG_Hash(const u32 input) {
    const u32 state = input * 747796405u + 2891336453u;
    const u32 word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}
