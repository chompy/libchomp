#ifndef CHOMPY_ANI_STATE
#define CHOMPY_ANI_STATE

#include "state.h"

class ChompyExampleState : public ChompState
{
public:

    static const char CHOMPY_ASSET[];
    static const char CHOMPY_ANIM[];
    static const char MUSIC_FILE[];

    ChompyExampleState(ChompCore* _core) : ChompState(_core)
    {
        chompySprite = nullptr;
        layer = nullptr;
    }

    void enter();
    void exit();
    void update();

protected:

    ChompGfxLayer* layer;
    ChompGfxSprite* chompySprite;


};

#endif