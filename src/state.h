#ifndef CHOMP_STATE_BASE
#define CHOMP_STATE_BASE

#include "core.h"

class ChompState
{
public:

    ChompState(ChompCore* _core);
    virtual ~ChompState();

    static void changeState(ChompState* s_currentState);
    static void updateState();

    // fires upon starting a new state
    virtual void enter();

    // fires when state is finished
    virtual void exit();

    // fire every frame while state is active
    virtual void update();

protected:
    static ChompState* s_currentState;
    ChompCore* core;

};

#endif