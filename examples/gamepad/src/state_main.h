#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "state.h"

#define INPUT_UPDATE_RATE 250

class ChompyStateMain : public Chomp::State
{
public:

    static const char* ACTIVE_GAMEPAD_COUNT_STRING;
    static const char* ACTIVE_GAMEPAD_INPUT_STRING;

    ChompyStateMain(Chomp::Core* _core) : Chomp::State(_core)
    {
        lastInputUpdate = 0;
        activeGamepadCount = 1000;
        activeGamepadCountText = NULL;
        activeInputText = NULL;
    }

    void enter();
    void exit();
    void update();

protected:

    uint16_t activeGamepadCount;
    Chomp::GfxText* activeGamepadCountText;

    uint32_t lastInputUpdate;
    Chomp::GfxText* activeInputText;

    void setActiveGamepadCountText();
    void setActiveInputText();

};

#endif