#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "state.h"
#include <iostream>

class ChompyStateMain : public ChompState
{
public:

    static const char SAMPLE_ASSET[];
    static const char SAMPLE_MUSIC[];

    ChompyStateMain(ChompCore* _core) : ChompState(_core)
    {
        sample = NULL;
    }

    void enter();
    void exit();
    void update();

protected:

    ChompSfxSample* sample;

};

#endif