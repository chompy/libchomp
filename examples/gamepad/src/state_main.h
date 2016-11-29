#ifndef CHOMPY_MAIN_STATE
#define CHOMPY_MAIN_STATE

#include "src/state.h"

#define INPUT_UPDATE_RATE 250

class ChompyStateMain : public ChompState
{
public:

    static const char* ACTIVE_GAMEPAD_COUNT_STRING;
    static const char* ACTIVE_GAMEPAD_INPUT_STRING;

    ChompyStateMain(ChompCore* _core) : ChompState(_core)
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
    ChompGfxText* activeGamepadCountText;

    uint32_t lastInputUpdate;
    ChompGfxText* activeInputText;

    void setActiveGamepadCountText();
    void setActiveInputText();

};

#endif