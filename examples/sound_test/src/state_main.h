#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "state.h"
#include <iostream>

class ChompyStateMain : public Chomp::State
{
public:

    static const char SAMPLE_ASSET[];
    static const char SAMPLE_MUSIC[];

    ChompyStateMain(Chomp::Core* _core) : Chomp::State(_core)
    {
        sample = NULL;
    }

    void enter();
    void exit();
    void update();

protected:

    Chomp::SfxSample* sample;

};

#endif