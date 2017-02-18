#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "state.h"

class ChompyStateMain : public Chomp::State
{
public:

    ChompyStateMain(Chomp::Core* _core) : Chomp::State(_core)
    {
    }

    void enter();
    void exit();
    void update();

protected:

};

#endif