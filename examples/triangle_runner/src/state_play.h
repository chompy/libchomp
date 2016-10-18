#ifndef CHOMPY_PLAY_STATE
#define CHOMPY_PLAY_STATE

#include "state.h"

#define PLAYER_MOVE_INC .03
#define WALL_SPACING .75

class ChompyStatePlay : public ChompState
{
public:

    ChompyStatePlay(ChompCore* _core) : ChompState(_core)
    {
        playerSprite = NULL;
        wallSprite = NULL;
        playerYTo = 0;
        playerYAt = 0;
        playerX = 0;
    }

    void enter();
    void exit();
    void update();

protected:

    float playerX;
    float playerYTo;
    float playerYAt;
    ChompGfxSprite* playerSprite;
    ChompGfxSprite* wallSprite;
    std::vector<std::vector<bool>> walls;

    void startRound();
    void generateWall();

};

#endif