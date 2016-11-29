#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "src/state.h"

class ChompyStateMain : public ChompState
{
public:

    ChompyStateMain(ChompCore* _core) : ChompState(_core)
    {
    }

    void enter();
    void exit();
    void update();

protected:

};

#endif