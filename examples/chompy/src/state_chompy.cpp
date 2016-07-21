#include "state_chompy.h"

const char ChompyExampleState::CHOMPY_ASSET[] = "chompy";
const char ChompyExampleState::CHOMPY_ANIM[] = "walk";

void ChompyExampleState::enter()
{
    if (!layer) {

        ChompGfxColor color;
        color.r = 255;
        color.g = 0;
        color.b = 0;
        color.a = 255;
        core->window.setDrawColor(&color);

        layer = core->window.newLayer(
            1000,
            1000,
            nullptr
        );
        layer->zIndex = 1;
        ChompGfxPosition pos1;
        pos1.x = 0;
        pos1.y = .5;
        ChompGfxPosition pos2;
        pos2.x = 1;
        pos2.y = .5;
        //layer->fill();
        layer->drawLine(&pos1, &pos2);
    }
    if (!chompySprite) {
        ChompGfxSize spriteSize;
        spriteSize.w = 1;
        spriteSize.h = 1;
        chompySprite = core->window.newSprite(
            (char*) ChompyExampleState::CHOMPY_ASSET,
            &spriteSize
        );
        chompySprite->setAnimation((char*) ChompyExampleState::CHOMPY_ANIM);
        chompySprite->zIndex = 2;
    }
}

void ChompyExampleState::exit()
{
    if (chompySprite) {
        delete chompySprite;
    }
    if (layer) {
        delete layer;
    }
}

void ChompyExampleState::update()
{
    chompySprite->updateAnimationFrame();
    core->window.addLayerToRenderer(chompySprite, nullptr, nullptr);
    core->window.addLayerToRenderer(layer, nullptr, nullptr);
}