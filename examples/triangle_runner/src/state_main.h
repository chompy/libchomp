#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include <iostream>
#include "state.h"
#include "state_play.h"

class ChompyStateMain : public Chomp::State
{
public:

    ChompyStateMain(Chomp::Core* _core, ChompyStatePlay* _playState) : Chomp::State(_core)
    {
        titleText = NULL;
        flavorText = NULL;
        startText = NULL;
        playState = _playState;
    }

    void enter();
    void exit();
    void update();

protected:

    ChompyStatePlay* playState;
    Chomp::GfxText* titleText;
    Chomp::GfxText* flavorText;
    Chomp::GfxText* startText;

};

#endif