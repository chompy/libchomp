#ifndef CHOMP_STATE_BASE
#define CHOMP_STATE_BASE

class ChompState
{
public:

    ChompState();
    virtual ~ChompState();

    static void changeState(ChompState* s_currentState);

    // fires upon starting a new state
    virtual void enter();

    // fires when state is finished
    virtual void exit();

    // fire every frame while state is active
    virtual void update();

protected:
    static ChompState* s_currentState;

};

#endif