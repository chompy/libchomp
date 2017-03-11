#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "state.h"
#include <iostream>
#include "component/map.h"

class ChompyStateMain : public ChompState
{
public:

    ChompyStateMain(ChompCore* _core) : ChompState(_core)
    {
        map = NULL;
    }

    void enter();
    void exit();
    void update();

protected:

    ChompyIsometricMap* map;

};

#endif