#ifndef CHOMPY_PLAY_STATE
#define CHOMPY_PLAY_STATE

#include "state.h"

#include <string>
#include <stdlib.h>
#include <time.h>

#define PLAYER_MOVE_INC .03
#define WALL_SPACING .75
#define WALL_V_GAP 3
#define WALLS_PER_ROUND 10
#define START_SPEED .015
#define ROUND_SPEED_MOD 1.1
#define MAX_SPEED .03
#define SPEED_UP_RATE 5
#define REDRAW_SCORE_RATE 1000

class ChompyStatePlay : public ChompState
{
public:

    ChompyStatePlay(ChompCore* _core) : ChompState(_core)
    {
        playerSprite = NULL;
        wallSprite = NULL;
        scoreText = NULL;
        playerYTo = 0;
        playerYAt = 0;
        playerX = 0;
        speed = 0;
        round = 0;
        lastScoreTextUpdate = 0;
    }

    void enter();
    void exit();
    void update();

protected:

    uint32_t score;
    uint16_t round;

    float playerX;
    float playerYTo;
    float playerYAt;
    float speed;
    ChompGfxSprite* playerSprite;
    ChompGfxSprite* wallSprite;
    std::vector<std::vector<bool>> walls;
    ChompGfxText* scoreText;
    uint32_t lastScoreTextUpdate;

    void startRound();
    void generateWall();
    void updateScore();

};

#endif