#ifndef CHOMP_GFX_STRUCTS_H
#define CHOMP_GFX_STRUCTS_H

#include <stdint.h>

#define FLIP_NONE 0
#define FLIP_HORIZONTAL 1
#define FLIP_VERTICAL 2
#define FLIP_BOTH 3

struct ChompGfxSize
{
    float w;
    float h;
};

struct ChompGfxPosition
{
    float x;
    float y;
    float z;
};

struct ChompGfxRect
{
    float x;
    float y;
    float w;
    float h;
};

struct ChompGfxColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

#endif