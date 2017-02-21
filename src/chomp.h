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

#ifndef CHOMP_H
#define CHOMP_H

#include <string>
#include "exception/sdl_exception.h"
#include "state.h"
#include "core.h"
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#define CHOMP_TARGET_FPS 60

namespace Chomp
{

    /**
     * Entry point for libchomp engine.
     */
    class Entry
    {

    public:

        /**
         * Name of developer's organization.
         * This should be set before calling the
         * 'start' method.
         */
        static std::string ORGANIZATION_NAME;

        /**
         * Name of application.
         * This should be set before calling the
         * 'start' method.
         */
        static std::string APPLICATION_NAME;

        /**
         * Core object.
         */
        Chomp::Core core;

        /**
         * Init libchomp and run given state.
         * @param state State to run
         */
        void start(Chomp::State* state);

        /**
         * Main loop for Emscripten platform
         * @param core Void pointer to core object
         */
        void emscriptenLoop(void* core);

        /**
         * Main loop.
         * @param core Core object
         * @return False if exiting
         */
        bool loop(Chomp::Core* core);

    protected:

        /**
         * Time in milliseconds to delay app
         * between each frame for desired FPS.
         */
        static float targetFrameDelay;

        /**
         * Last tick a frame was rendered.
         */
        static uint32_t lastFrameTime;

    };

};

#endif