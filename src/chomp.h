#ifndef CHOMP_H
#define CHOMP_H

#include <SDL2/SDL.h>
#include "exception.h"
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