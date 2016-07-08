#ifndef CHOMP_GFX_STRUCTS_H
#define CHOMP_GFX_STRUCTS_H

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