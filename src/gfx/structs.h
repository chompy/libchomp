#ifndef CHOMP_GFX_STRUCTS_H
#define CHOMP_GFX_STRUCTS_H

#include <stdint.h>

#define FLIP_NONE 0
#define FLIP_HORIZONTAL 1
#define FLIP_VERTICAL 2
#define FLIP_BOTH 3

/**
 * Struct meant to contain size data.
 */
struct ChompGfxSize
{
    float w; /**< width >*/
    float h; /**< height >*/
};

/**
 * Struct meant to contain position data.
 */
struct ChompGfxPosition
{
    float x; /**< x position >*/
    float y; /**< y position >*/
};

/**
 * Struct meant to contain rectangle data.
 */
struct ChompGfxRect
{
    float x; /**< x position >*/
    float y; /**< y position >*/
    float w; /**< width >*/
    float h; /**< height >*/
};

/**
 * Struct meant to contain color data.
 */
struct ChompGfxColor
{
    uint8_t r; /**< red >*/
    uint8_t g; /**< green >*/
    uint8_t b; /**< blue >*/
    uint8_t a; /**< alpha >*/
};

#endif