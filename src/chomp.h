#ifndef CHOMP_H
#define CHOMP_H

#include <SDL2/SDL.h>
#include "exception.h"
#include "state.h"
#include "asset.h"
#include "gfx/window.h"

class Chomp
{
public:

    Chomp();
    ~Chomp();

    ChompAsset asset;
    ChompGfxWindow window;

};

#endif