#ifndef CHOMPY_PLAY_STATE
#define CHOMPY_PLAY_STATE

#include "state.h"
#include "player.h"

class ChompyStatePlay : public ChompState
{
public:

    ChompyStatePlay(ChompCore* _core) : ChompState(_core)
    {
        player = NULL;
    }

    void enter();
    void exit();
    void update();

protected:
    ChompyPlayer* player;
};

#endif