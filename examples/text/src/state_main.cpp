#include "state_main.h"

void ChompyStateMain::enter()
{
    if (!textLayer) {
        Chomp::GfxSize layerSize;
        layerSize.w = 640;
        layerSize.h = 480;
        
        textLayer = core->gfx.newTextLayer("impact", 128, &layerSize);
        textLayer->setDrawMode(CHOMP_GFX_TEXT_DRAW_MODE_BLENDED);

        Chomp::GfxColor color;
        color.r = 255;
        color.g = 0;
        color.b = 0;
        color.a = 255;
        core->gfx.setDrawColor(&color);

        textLayer->setText(
            "Hello World!",
            CHOMP_GFX_TEXT_CENTER,
            CHOMP_GFX_TEXT_MIDDLE
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
    Chomp::GfxSize windowSize = core->gfx.getWindowSize();
    Chomp::GfxRect dstRect;
    dstRect.x = (windowSize.w / 2) - (textLayer->getSize().w / 2);
    dstRect.y = (windowSize.h / 2) - (textLayer->getSize().h / 2);
    dstRect.w = textLayer->getSize().w;
    dstRect.h = textLayer->getSize().h;
    core->gfx.addLayerToRenderer(textLayer, NULL, &dstRect);
}