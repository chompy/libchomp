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
        color.g = 0;
        color.b = 0;
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
    ChompGfxSize windowSize = core->gfx.getWindowSize();
    ChompGfxRect dstRect;
    dstRect.x = (windowSize.w / 2) - (textLayer->size.w / 2);
    dstRect.y = (windowSize.h / 2) - (textLayer->size.h / 2);
    dstRect.w = textLayer->size.w;
    dstRect.h = textLayer->size.h;
    core->gfx.addLayerToRenderer(textLayer, NULL, &dstRect);
}