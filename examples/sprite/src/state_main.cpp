#include "state_main.h"

const char ChompyStateMain::CHOMPY_ASSET[] = "chompy";
const char ChompyStateMain::CHOMPY_ANIM[] = "walk";

void ChompyStateMain::enter()
{
    if (!chompySprite) {
        chompySprite = core->gfx.newSprite(
            (char*) ChompyStateMain::CHOMPY_ASSET
        );
        chompySprite->setAnimation((char*) ChompyStateMain::CHOMPY_ANIM);
        chompySprite->zIndex = 2;
    }
    resize();
}

void ChompyStateMain::exit()
{
    if (chompySprite) {
        delete chompySprite;
    }
}

void ChompyStateMain::update()
{
    if (!chompySprite) {
        return;
    }
    chompySprite->updateAnimationFrame();
    Chomp::GfxSize windowSize = core->gfx.getWindowSize();
    Chomp::GfxSize spriteSize = chompySprite->getSize();
    spriteSize.w = spriteSize.w * scaleFactor;
    spriteSize.h = spriteSize.h * scaleFactor;
    Chomp::GfxRect destRect;
    destRect.x = (windowSize.w / 2) - (spriteSize.w / 2);
    destRect.y = (windowSize.h / 2) - (spriteSize.h / 2);
    destRect.w = spriteSize.w;
    destRect.h = spriteSize.h;
    core->gfx.addLayerToRenderer(chompySprite, NULL, &destRect);
}

void ChompyStateMain::resize()
{
    Chomp::GfxSize windowSize = core->gfx.getWindowSize();
    if (windowSize.w > windowSize.h) {
        scaleFactor = ((float) windowSize.w / CHOMP_GFX_DEFAULT_WINDOW_W) * 2;
        return;
    }
    scaleFactor = ((float) windowSize.h / CHOMP_GFX_DEFAULT_WINDOW_H) * 2;
}