/**
    This file is part of Libchomp.

    Libchomp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Libchomp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Libchomp.  If not, see <http://www.gnu.org/licenses/>.
**/

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
        int32_t w; /**< width >*/
        int32_t h; /**< height >*/
    };

    /**
     * Struct meant to contain position data.
     */
    struct GfxPosition
    {
        int32_t x; /**< x position >*/
        int32_t y; /**< y position >*/
    };

    /**
     * Struct meant to contain rectangle data.
     */
    struct GfxRect
    {
        int32_t x; /**< x position >*/
        int32_t y; /**< y position >*/
        int32_t w; /**< width >*/
        int32_t h; /**< height >*/
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