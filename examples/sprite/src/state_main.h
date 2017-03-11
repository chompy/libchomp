#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "state.h"

class ChompyStateMain : public Chomp::State
{
public:

    static const char CHOMPY_ASSET[];
    static const char CHOMPY_ANIM[];

    ChompyStateMain(Chomp::Core* _core) : Chomp::State(_core)
    {
        chompySprite = NULL;
    }

    void enter();
    void exit();
    void update();
    void resize();

protected:

    float scaleFactor;

    Chomp::GfxSprite* chompySprite;

};

#endif