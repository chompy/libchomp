/**
    This file is part of Libchomp.

    Libchomp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Libchomp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Libchomp.  If not, see <http://www.gnu.org/licenses/>.
**/

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
         * Application specific path where user
         * data should be stored.
         * @see https://wiki.libsdl.org/SDL_GetPrefPath
         */
        static char* PREF_PATH;

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