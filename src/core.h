#ifndef CHOMP_CORE_H
#define CHOMP_CORE_H

#include "sdl_includes.h"
#include "asset/asset.h"
#include "asset/config.h"
#include "gfx/gfx.h"
#include "sfx/sfx.h"
#include "input/input.h"

namespace Chomp
{

    /**
     * Libchomp Core
     */
    class Core
    {
    public:

        /**
         * Graphics object
         */
        Chomp::Gfx gfx;

        /**
         * Sound effects object
         */
        Chomp::Sfx sfx;

        /**
         * Input object
         */
        Chomp::Input input;

        /**
         * Last frame delta time.
         */
        float deltaTime;

        /**
         * Get time since start of app.
         * @return Milliseconds since start
         */
        uint32_t getTicks() { return SDL_GetTicks(); }

    };
};

#endif