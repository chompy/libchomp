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
        chompySprite->setAnimation((char*) ChompyExampleState::CHOMPY_ANIM);
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
    chompySprite->updateAnimationFrame();
    core->window.addLayerToRenderer(chompySprite, nullptr, nullptr);
}