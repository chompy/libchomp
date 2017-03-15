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

#ifndef CHOMP_GFX_GRID_H
#define CHOMP_GFX_GRID_H

#include "structs.h"

namespace Chomp
{

    /**
     * Class for calculating pixel coorindates when treating
     * the window as a grid
     */
    class GfxGrid
    {

    public:

        /**
         * Columns in grid.
         */
        uint16_t gridCols;

        /**
         * Rows in grid.
         */
        uint16_t gridRows;

        /**
         * Pixel size of space to convert to grid
         */
        Chomp::GfxSize pixelSize;

        /**
         * Constructor.
         * @param _pixelSize Pixel size of space to convert to grid\
         * @param _gridCols Columns in grid
         * @param _gridRows Rows in grid
         */
        GfxGrid(Chomp::GfxSize _pixelSize, uint16_t _gridCols, uint16_t _gridRows);

        /**
         * Get pixel size of 1x1 grid space.
         * @return Struct containing pixel width and height
         */
        Chomp::GfxSize getSize() { return getSize(1, 1); }

        /**
         * Get pixel size of given grid space.
         * @param cols Number of columns
         * @param rows Number of rows
         * @return Struct containing pixel width and height
         */
        Chomp::GfxSize getSize(uint16_t cols, uint16_t rows);

        /**
         * Get number of pixels left over after
         * space is divided in to a grid.
         * @return Struct containing pixel width and height
         */
        Chomp::GfxSize getRemainingPixels();

    };

};

#endif