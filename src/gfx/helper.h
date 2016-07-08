#ifndef CHOMP_GFX_HELPER_H
#define CHOMP_GFX_HELPER_H

#include "structs.h"

class ChompGfxHelper
{

public:

    static void toPixelSize(ChompGfxSize* size, uint16_t* width, uint16_t* height);
    static ChompGfxSize fromPixelSize(uint16_t width, uint16_t height);

};

#endif