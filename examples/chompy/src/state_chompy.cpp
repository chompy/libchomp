#include "state_chompy.h"

const char ChompyExampleState::CHOMPY_ASSET[] = "chompy";
const char ChompyExampleState::CHOMPY_ANIM[] = "walk";

void ChompyExampleState::enter()
{
    if (!chompySprite) {
        ChompGfxSize spriteSize;
        spriteSize.w = 1;
        spriteSize.h = 1;
        chompySprite = core->window.newSprite(
            (char*) ChompyExampleState::CHOMPY_ASSET,
            &spriteSize
        );
        chompySprite->setFrame(12);
    }
}

void ChompyExampleState::exit()
{
    if (chompySprite) {
        delete chompySprite;
    }
}

void ChompyExampleState::update()
{
    core->window.addLayerToRenderer(chompySprite, nullptr, nullptr);
}