#ifndef CHOMP_CORE_H
#define CHOMP_CORE_H

#include <SDL2/SDL.h>
#include "asset/asset.h"
#include "gfx/gfx.h"
#include "sfx/sfx.h"
#include "input/input.h"

class ChompCore
{
public:

    ChompGfx gfx;
    ChompSfx sfx;
    ChompInput input;

};

#endif