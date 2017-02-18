#ifndef CHOMP_H
#define CHOMP_H

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