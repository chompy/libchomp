#include "state_main.h"

void ChompyStateMain::enter()
{
    grid.gridCols = 3;
    grid.gridRows = 3;
    resize();
}

void ChompyStateMain::exit()
{

}

void ChompyStateMain::update()
{
    core->gfx.addLayerToRenderer(layer, NULL, NULL);
}

void ChompyStateMain::resize()
{
    grid.pixelSize = core->gfx.getWindowSize();
    if (layer) {
        delete layer;
    }

    Chomp::GfxColor color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    core->gfx.setDrawColor(&color);

    layer = core->gfx.newLayer(&grid.pixelSize);
    Chomp::GfxPosition pos1;
    Chomp::GfxPosition pos2;
    Chomp::GfxSize gridSize = grid.getSize();
    for (uint16_t cols = 1; cols < grid.gridCols; cols++) {
        pos1.x = gridSize.w * cols;
        pos1.y = 0;
        pos2.x = pos1.x;
        pos2.y = grid.pixelSize.h;
        layer->drawLine(&pos1, &pos2);
        for (uint16_t rows = 1; rows < grid.gridRows; rows++) {
            pos1.x = 0;
            pos1.y = gridSize.h * rows;
            pos2.x = grid.pixelSize.w;
            pos2.y = pos1.y;
            layer->drawLine(&pos1, &pos2);            
        }
    }

}