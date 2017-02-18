#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "state.h"

class ChompyStateMain : public Chomp::State
{
public:

    ChompyStateMain(Chomp::Core* _core) : Chomp::State(_core)
    {
        layer = NULL;
    }

    void enter();
    void exit();
    void update();

protected:

    void rectToPixelCoords(Chomp::GfxRect* rect, Chomp::GfxRect* offset, uint16_t* x, uint16_t* y, uint16_t* w, uint16_t* h);

    Chomp::GfxLayer* layer;

};

#endif