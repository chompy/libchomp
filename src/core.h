#ifndef CHOMP_CORE_H
#define CHOMP_CORE_H

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

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