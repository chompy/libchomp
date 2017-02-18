#ifndef CHOMP_GFX_STRUCTS_H
#define CHOMP_GFX_STRUCTS_H

#include <stdint.h>

#define CHOMP_GFX_FLIP_NONE 0
#define CHOMP_GFX_FLIP_HORIZONTAL 1
#define CHOMP_GFX_FLIP_VERTICAL 2
#define CHOMP_GFX_FLIP_BOTH 3

namespace Chomp
{

    /**
     * Struct meant to contain size data.
     */
    struct GfxSize
    {
        float w; /**< width >*/
        float h; /**< height >*/
    };

    /**
     * Struct meant to contain position data.
     */
    struct GfxPosition
    {
        float x; /**< x position >*/
        float y; /**< y position >*/
    };

    /**
     * Struct meant to contain rectangle data.
     */
    struct GfxRect
    {
        float x; /**< x position >*/
        float y; /**< y position >*/
        float w; /**< width >*/
        float h; /**< height >*/
    };

    /**
     * Struct meant to contain color data.
     */
    struct GfxColor
    {
        uint8_t r; /**< red >*/
        uint8_t g; /**< green >*/
        uint8_t b; /**< blue >*/
        uint8_t a; /**< alpha >*/
    };

};

#endif