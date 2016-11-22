#ifndef CHOMP_CORE_H
#define CHOMP_CORE_H

#include "sdl_includes.h"
#include "asset/asset.h"
#include "asset/config.h"
#include "gfx/gfx.h"
#include "sfx/sfx.h"
#include "input/input.h"

/**
 * Libchomp Core
 */
class ChompCore
{
public:

    /**
     * Graphics object
     */
    ChompGfx gfx;

    /**
     * Sound effects object
     */
    ChompSfx sfx;

    /**
     * Input object
     */
    ChompInput input;

    /**
     * Last frame delta time.
     */
    float deltaTime = 1;

    /**
     * Get time since start of app.
     * @return Milliseconds since start
     */
    uint32_t getTicks() { return SDL_GetTicks(); }

};

#endif