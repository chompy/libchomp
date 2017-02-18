#ifndef CHOMPY_ANI_STATE
#define CHOMPY_ANI_STATE

#include "state.h"

class ChompyExampleState : public Chomp::State
{
public:

    static const char CHOMPY_ASSET[];
    static const char CHOMPY_ANIM[];

    ChompyExampleState(Chomp::Core* _core) : Chomp::State(_core)
    {
        chompySprite = NULL;
        layer = NULL;
    }

    void enter();
    void exit();
    void update();

protected:

    Chomp::GfxLayer* layer;
    Chomp::GfxSprite* chompySprite;


};

#endif