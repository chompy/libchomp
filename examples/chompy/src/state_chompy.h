#ifndef CHOMPY_ANI_STATE
#define CHOMPY_ANI_STATE

#include "state.h"

class ChompyExampleState : public ChompState
{
public:

    static const char CHOMPY_ASSET[];
    static const char CHOMPY_ANIM[];

    ChompyExampleState(ChompCore* _core) : ChompState(_core)
    {
        //chompySprite = 0;
    }

    void enter();
    void exit();
    void update();

protected:

    ChompGfxLayer* layer;
    ChompGfxSprite* chompySprite;


};

#endif