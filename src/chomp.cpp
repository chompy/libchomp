#include "chomp.h"

Chomp::Chomp()
{

    // init sdl systems
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw ChompSdlInitException();
        return;
    }

}

Chomp::~Chomp()
{

}

