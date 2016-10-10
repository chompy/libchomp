#ifndef CHOMP_H
#define CHOMP_H

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include "exception/sdl_exception.h"
#include "state.h"
#include "core.h"

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

    uint32_t lastFrameTime;

};

#endif