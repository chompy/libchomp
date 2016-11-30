#ifndef CHOMPY_PLAY_STATE
#define CHOMPY_PLAY_STATE

#include "state.h"

#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

#define WALL_SPACING 1.25
#define WALL_V_GAP 3
#define WALLS_PER_ROUND 10

#define VER_MOVE_INC .025
#define MAX_SPEED .03
#define SPEED_ACCEL .0005
#define BOUNCE_SPEED .01

#define GAME_AREA_W 1.0
#define GAME_AREA_H 1.0
#define SCORE_PER_WALL 1
#define START_LIVES 3

#define INPUT_MOUSE 0
#define INPUT_KEYBOARD 1
#define INPUT_GAMEPAD 2

class ChompyStatePlay : public ChompState
{
public:

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
        round = 0;
        lives = START_LIVES;
        lastScoreX = 0;
        inputDevice = INPUT_MOUSE;
    }

    void enter();
    void exit();
    void update();

protected:

    // config vars
    float wallSpacing;
    uint8_t wallGap;
    uint16_t wallsPerRound = 10;
    float playerVerticalSpeed = .03;
    float playerMaxSpeed = .03;
    float playerAccelRate = .0005;
    float playerBounce = .01;

    // state vars
    uint8_t inputDevice;
    uint8_t lives;
    uint32_t score;
    uint16_t round;
    uint16_t lastScoreX;
    ChompGfxPosition playerPos;
    float playerYTo;
    float speed;
    std::vector<std::vector<bool> > walls;

    // gfx layers
    ChompGfxLayer* gameLayer;
    ChompGfxSprite* playerSprite;
    ChompGfxSprite* wallSprite;
    ChompGfxText* scoreText;

    void startRound();
    void generateWall();
    void updateScore();

};

#endif