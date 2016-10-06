#include "state_main.h"

void ChompyStateMain::enter()
{
    if (!layer) {
        layer = core->gfx.newLayer(
            1000,
            1000,
            nullptr
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
    rect.x = .1;
    rect.y = .1;
    rect.w = .8;
    rect.h = .8;
    rectToPixelCoords(&rect, &mx, &my, &mw, &mh);
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
    rect.x = .99;
    rect.y = .1;
    rect.w = .3;
    rect.h = .3;
    rectToPixelCoords(&rect, &mx, &my, &mw, &mh);
    std::cout << mx << std::endl;
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

    core->gfx.addLayerToRenderer(layer, nullptr, nullptr);
}

void ChompyStateMain::rectToPixelCoords(ChompGfxRect* rect, uint16_t* x, uint16_t* y, uint16_t* w, uint16_t* h)
{
    ChompGfxSize size;
    size.w = rect->x;
    size.h = rect->y;
    core->gfx.toPixelSize(&size, x, y);
    size.w = rect->w;
    size.h = rect->h;
    core->gfx.toPixelSize(&size, w, h);
}