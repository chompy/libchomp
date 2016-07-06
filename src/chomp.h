#ifndef CHOMP_H
#define CHOMP_H

#include <SDL2/SDL.h>
#include "asset.h"
#include "gfx.h"

class Chomp
{
public:

    Chomp();
    ~Chomp();

    ChompAsset asset;
    ChompGfxWindow window;

};

#endif