#ifndef CHOMP_CORE_H
#define CHOMP_CORE_H

#include "sdl_includes.h"
#include "asset/asset.h"
#include "asset/config.h"
#include "gfx/gfx.h"
#include "sfx/sfx.h"
#include "input/input.h"

class ChompCore
{
public:

    ChompGfx gfx;
    ChompSfx sfx;
    ChompInput input;

    float deltaTime = 1;

    uint32_t getTicks() { return SDL_GetTicks(); }

};

#endif