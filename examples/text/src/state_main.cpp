#include "state_main.h"

void ChompyStateMain::enter()
{
    if (!textLayer) {
        ChompGfxSize layerSize;
        layerSize.w = 1;
        layerSize.h = 1;
        textLayer = core->gfx.newTextLayer("impact", 48, &layerSize);

        ChompGfxColor color;
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
        core->gfx.setDrawColor(&color);

        textLayer->setText(
            "Hello World!",
            TEXT_CENTER,
            TEXT_MIDDLE
        );
        textLayer->zIndex = 1;
    }
}

void ChompyStateMain::exit()
{
    if (textLayer) {
        delete textLayer;
    }
}

void ChompyStateMain::update()
{
    core->gfx.addLayerToRenderer(textLayer, nullptr, nullptr);
}