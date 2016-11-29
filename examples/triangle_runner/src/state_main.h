#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include <iostream>
#include "src/state.h"
#include "state_play.h"

class ChompyStateMain : public ChompState
{
public:

    ChompyStateMain(ChompCore* _core, ChompyStatePlay* _playState) : ChompState(_core)
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
    ChompGfxText* titleText;
    ChompGfxText* flavorText;
    ChompGfxText* startText;

};

#endif