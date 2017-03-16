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
    void resize();

protected:

    Chomp::GfxGrid grid;
    Chomp::GfxLayer* layer;

};

#endif