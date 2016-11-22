#ifndef CHOMP_H
#define CHOMP_H

#include "exception/sdl_exception.h"
#include "state.h"
#include "core.h"
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#define TARGET_FPS 60

/**
 * Main class for libchomp
 */
class Chomp
{
public:

    /**
     * Constructor.
     */
    Chomp();

    /**
     * Destructor.
     */
    ~Chomp();

    /**
     * Core object.
     */
    ChompCore core;

    /**
     * Init libchomp and run given state.
     * @param state State to run
     */
    void start(ChompState* state);

    /**
     * Main loop for Emscripten platform
     * @param core Void pointer to core object
     */
    static void emscriptenLoop(void* core);

    /**
     * Main loop.
     * @param core Core object
     * @return False if exiting
     */
    static bool loop(ChompCore* core);

private:

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

#endif