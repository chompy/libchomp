#ifndef CHOMP_STATE_BASE
#define CHOMP_STATE_BASE

#include "core.h"

/**
 * Libchomp State
 */
class ChompState
{
public:

    /**
     * Constructor.
     * @param _core Core object
     */
    ChompState(ChompCore* _core);

    /**
     * Destructor.
     */
    virtual ~ChompState();

    /**
     * Change active state.
     * @param s_currentState State to change to
     */
    static void changeState(ChompState* s_currentState);

    /**
     * Call update method of current active state.
     */
    static void updateState();

    /**
     * Called when state is made active.
     */
    virtual void enter();

    /**
     * Called when state is made inactive.
     */
    virtual void exit();

    /**
     * Called every frame state is active.
     */
    virtual void update();

protected:

    /**
     * Current active state.
     */
    static ChompState* s_currentState;

    /**
     * Core object.
     */
    ChompCore* core;

};

#endif