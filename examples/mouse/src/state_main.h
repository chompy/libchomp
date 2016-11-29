#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "src/state.h"

class ChompyStateMain : public ChompState
{
public:

    ChompyStateMain(ChompCore* _core) : ChompState(_core)
    {
        layer = NULL;
    }

    void enter();
    void exit();
    void update();

protected:

    void rectToPixelCoords(ChompGfxRect* rect, ChompGfxRect* offset, uint16_t* x, uint16_t* y, uint16_t* w, uint16_t* h);

    ChompGfxLayer* layer;

};

#endif