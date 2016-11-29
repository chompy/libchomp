#include "state_main.h"

void ChompyStateMain::enter()
{
    if (!layer) {
        ChompGfxSize size;
        size.w = 1;
        size.h = 1;
        layer = core->gfx.newLayer(
            1000,
            1000,
            &size
        );
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
    ChompGfxSize windowSize = core->gfx.getWindowSize();
    ChompGfxRect dstRect;
    dstRect.x = (windowSize.w / 2) - (layer->size.w / 2);
    dstRect.y = (windowSize.h / 2) - (layer->size.h / 2);
    dstRect.w = layer->size.w;
    dstRect.h = layer->size.h;

    // init color
    ChompGfxColor color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    core->gfx.setDrawColor(&color);

    // clear layer
    layer->fill();

    // init rect
    ChompGfxRect rect;

    // init mouse coords
    uint16_t mx,my,mw,mh;

    // rect 1
    rect.w = .7;
    rect.h = .8;
    rect.x = 0;
    rect.y = .1;

    rectToPixelCoords(&rect, &dstRect, &mx, &my, &mw, &mh);
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    if (core->input.mouse.pressed(MOUSE_BUTTON_LEFT) && core->input.mouse.in(mx, my, mw, mh)) {
        color.r = 0;
        color.g = 0;
        color.b = 255;
        color.a = 255;
    }
    core->gfx.setDrawColor(&color);
    layer->drawFillRect(&rect);

    // rect 2
    rect.x = .8;
    rect.y = .1;
    rect.w = .2;
    rect.h = .2;
    rectToPixelCoords(&rect, &dstRect, &mx, &my, &mw, &mh);
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    if (core->input.mouse.pressed(MOUSE_BUTTON_LEFT) && core->input.mouse.in(mx, my, mw, mh)) {
        color.r = 0;
        color.g = 0;
        color.b = 255;
        color.a = 255;
    }
    core->gfx.setDrawColor(&color);
    layer->drawFillRect(&rect);


    core->gfx.addLayerToRenderer(layer, NULL, &dstRect);
}

void ChompyStateMain::rectToPixelCoords(ChompGfxRect* rect, ChompGfxRect* offset, uint16_t* x, uint16_t* y, uint16_t* w, uint16_t* h)
{
    ChompGfxSize size;
    size.w = rect->x + offset->x;
    size.h = rect->y + offset->y;
    core->gfx.toPixelSize(&size, x, y);
    size.w = rect->w;
    size.h = rect->h;
    core->gfx.toPixelSize(&size, w, h);
}