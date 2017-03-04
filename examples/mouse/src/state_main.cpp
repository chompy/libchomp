#include "state_main.h"

void ChompyStateMain::enter()
{
    if (!layer) {
        Chomp::GfxSize size;
        size.w = 640;
        size.h = 480;
        layer = core->gfx.newLayer(&size);
    }
}

void ChompyStateMain::exit()
{
    if (layer) {
        delete layer;
    }
}

void ChompyStateMain::update()
{

    // layer position
    Chomp::GfxSize windowSize = core->gfx.getWindowSize();
    Chomp::GfxRect dstRect;
    dstRect.x = (windowSize.w / 2) - (layer->getSize().w / 2);
    dstRect.y = (windowSize.h / 2) - (layer->getSize().h / 2);
    dstRect.w = layer->getSize().w;
    dstRect.h = layer->getSize().h;

    // init color
    Chomp::GfxColor color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    core->gfx.setDrawColor(&color);

    // clear layer
    layer->fill();

    // init rect
    Chomp::GfxRect rect;

    // rect 1
    rect.w = 480;
    rect.h = 320;
    rect.x = 0;
    rect.y = 64;

    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    if (core->input.mouse.pressed(CHOMP_INPUT_MOUSE_BUTTON_LEFT) && core->input.mouse.in(rect.x, rect.y, rect.w, rect.h)) {
        color.r = 0;
        color.g = 0;
        color.b = 255;
        color.a = 255;
    }
    core->gfx.setDrawColor(&color);
    layer->drawFillRect(&rect);

    // rect 2
    rect.x = 500;
    rect.y = 64;
    rect.w = 120;
    rect.h = 120;
    
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    if (core->input.mouse.pressed(CHOMP_INPUT_MOUSE_BUTTON_LEFT) && core->input.mouse.in(rect.x, rect.y, rect.w, rect.h)) {
        color.r = 0;
        color.g = 0;
        color.b = 255;
        color.a = 255;
    }
    core->gfx.setDrawColor(&color);
    layer->drawFillRect(&rect);


    core->gfx.addLayerToRenderer(layer, NULL, &dstRect);
}
