#ifndef CHOMP_H
#define CHOMP_H

#include "exception/sdl_exception.h"
#include "state.h"
#include "core.h"
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#define TARGET_FPS 60

class Chomp
{
public:

    Chomp();
    ~Chomp();

    ChompCore core;

    void start(ChompState* state);

    static void emscriptenLoop(void* core);
    static bool loop(ChompCore* core);

private:

    static float targetFrameDelay;
    static uint32_t lastFrameTime;

};

#endif