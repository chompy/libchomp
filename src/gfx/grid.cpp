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

#include "grid.h"

Chomp::GfxGrid::GfxGrid(Chomp::GfxSize _pixelSize, uint16_t _gridCols, uint16_t _gridRows)
{
    pixelSize = _pixelSize;
    gridCols = _gridCols;
    gridRows = _gridRows;
}

Chomp::GfxSize Chomp::GfxGrid::getSize(uint16_t cols, uint16_t rows)
{
    Chomp::GfxSize gridSize;
    gridSize.w = (pixelSize.w / gridCols) * cols;
    gridSize.h = (pixelSize.h / gridRows) * rows;
    return gridSize;
}

Chomp::GfxSize Chomp::GfxGrid::getRemainingPixels()
{
    Chomp::GfxSize remaining;
    remaining.w = pixelSize.w % gridCols;   
    remaining.h = pixelSize.h % gridRows;
    return remaining;
}