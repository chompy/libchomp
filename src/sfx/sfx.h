#ifndef CHOMP_SFX_H
#define CHOMP_SFX_H

#include <string>
#include <SDL2/SDL.h>
#include "SDL2/SDL_mixer.h"
#include "../exception.h"

class ChompSfx {

public:

    ChompSfx();
    ~ChompSfx();

    void loadMusic(char* name);
    void loadChunk(char* name);

};

#endif