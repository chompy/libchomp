#ifndef CHOMPY_PLAYER
#define CHOMPY_PLAYER

#include "chomp.h"

#define MOVE_INC .03

class ChompyPlayer
{
public:

    ChompyPlayer(ChompCore* _core);
    ~ChompyPlayer();

    float y;
    ChompGfxSprite* sprite;

    void loop();
    void draw();

protected:

    float currentY;

    ChompCore* core;
    

};

#endif