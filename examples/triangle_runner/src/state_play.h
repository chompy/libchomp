#ifndef CHOMPY_PLAY_STATE
#define CHOMPY_PLAY_STATE

#include "state.h"

#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

#define PLAYER_MOVE_INC .03
#define WALL_SPACING 1
#define WALL_V_GAP 3
#define WALLS_PER_ROUND 10
#define START_SPEED .015
#define ROUND_SPEED_MOD 1.001
#define MAX_SPEED .04
#define SPEED_ACCEL .001
#define SPEED_UP_RATE 5
#define REDRAW_SCORE_RATE 1000
#define GAME_AREA_W 1.0
#define GAME_AREA_H 1.0
#define SCORE_PER_WALL 100
#define START_LIVES 3;
#define HIT_STOP_TIME 750

class ChompyStatePlay : public ChompState
{
public:

    static const char* PLAYER_ANIM_STOP;
    static const char* PLAYER_ANIM_MOVE;
    static const char* PLAYER_ANIM_DIE;

    ChompyStatePlay(ChompCore* _core) : ChompState(_core)
    {
        gameLayer = NULL;
        playerSprite = NULL;
        wallSprite = NULL;
        scoreText = NULL;
        playerPos.x = 0;
        playerPos.y = 0;
        playerYTo = 0;
        speed = 0;
        maxSpeed = 0;
        round = 0;
        lives = START_LIVES;
        lastScoreX = 0;
        hitStopTime = 0;
    }

    void enter();
    void exit();
    void update();

protected:

    uint8_t lives;
    uint32_t score;
    uint16_t round;
    uint16_t lastScoreX;
    uint32_t hitStopTime;

    ChompGfxPosition playerPos;
    float playerYTo;
    float speed;
    float maxSpeed;

    ChompGfxLayer* gameLayer;
    ChompGfxSprite* playerSprite;
    ChompGfxSprite* wallSprite;
    std::vector<std::vector<bool>> walls;
    ChompGfxText* scoreText;

    void startRound();
    void generateWall();
    void updateScore();

};

#endif