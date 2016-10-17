#include "player.h"

ChompyPlayer::ChompyPlayer(ChompCore* _core)
{
    core = _core;
    ChompGfxSize size;
    size.w = .125;
    size.h = .125;
    sprite = core->gfx.newSprite(
        "player",
        &size
    );
    sprite->setAnimation("stop");
    ChompGfxSize windowSize = core->gfx.getWindowSize();
    currentY = (windowSize.h - sprite->size.h) / 2;
    y = currentY;
}

ChompyPlayer::~ChompyPlayer()
{
    if (sprite) {
        delete sprite;
    }
}

void ChompyPlayer::loop()
{
    if (currentY > y) {
        currentY -= MOVE_INC;
    } else if (currentY < y) {
        currentY += MOVE_INC;
    }
    if (fabs(currentY - y) < MOVE_INC) {
        currentY = y;
    }
    ChompGfxSize windowSize = core->gfx.getWindowSize();
    if (currentY > windowSize.h - sprite->size.h) {
        currentY = windowSize.h - sprite->size.h;
    }
}

void ChompyPlayer::draw()
{
    if (!sprite) {
        return;
    }

    ChompGfxSize windowSize = core->gfx.getWindowSize();
    ChompGfxRect rect;
    rect.x = (windowSize.w - sprite->size.w) / 2;
    rect.y = currentY;
    rect.w = sprite->size.w;
    rect.h = sprite->size.h;
    core->gfx.addLayerToRenderer(sprite, NULL, &rect);
}