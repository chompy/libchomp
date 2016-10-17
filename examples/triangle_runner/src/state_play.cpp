#include "state_play.h"

void ChompyStatePlay::enter()
{
    player = new ChompyPlayer(core);
}

void ChompyStatePlay::exit()
{
    if (player) {
        delete player;
    }
}

void ChompyStatePlay::update()
{
    if (player) {

        ChompGfxSize mouse = core->gfx.fromPixelSize(
            core->input.mouse.x,
            core->input.mouse.y
        );
        player->y = mouse.h - (player->sprite->size.h / 2);

        player->loop();
        player->draw();
    }
}