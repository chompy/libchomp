#include "state_play.h"

void ChompyStatePlay::enter()
{
    // seed random
    srand (time(NULL));
    // hide cursor
    core->gfx.setCursorVisibility(false);
    // load player sprite
    ChompGfxSize size;
    size.w = .125;
    size.h = .125;
    playerSprite = core->gfx.newSprite(
        "player",
        &size
    );
    // load wall sprite
    size.w = 0.04167;
    wallSprite = core->gfx.newSprite(
        "wall",
        &size
    );
    // load score text
    size.w = .4;
    scoreText = core->gfx.newTextLayer("tahoma", 24, &size);
    scoreText->setText("SCORE: 0");
    // center player
    ChompGfxSize windowSize = core->gfx.getWindowSize();
    playerYTo = (windowSize.h - playerSprite->size.h) / 2;
    playerYAt = playerYTo;
    playerX = 0;
    speed = START_SPEED;

    // start first round
    round = 0;
    startRound();
}

void ChompyStatePlay::exit()
{
    if (playerSprite) {
        delete playerSprite;
    }
    if (wallSprite) {
        delete wallSprite;
    }
    core->gfx.setCursorVisibility(true);
}

void ChompyStatePlay::update()
{
    // current window size
    ChompGfxSize windowSize = core->gfx.getWindowSize();

    // vertical offset
    float vOffset = ((windowSize.h / 2) - .5);

    // player movement
    if (playerYAt > playerYTo) {
        playerYAt -= (PLAYER_MOVE_INC * core->deltaTime);
    } else if (playerYAt < playerYTo) {
        playerYAt += (PLAYER_MOVE_INC * core->deltaTime);
    }
    if (fabs(playerYAt - playerYTo) < PLAYER_MOVE_INC) {
        playerYAt = playerYTo;
    }
    if (playerYAt < 0) {
        playerYAt = 0;
    } else if (playerYAt > windowSize.h - playerSprite->size.h) {
        playerYAt = windowSize.h - playerSprite->size.h;
    }
    ChompGfxSize mouse = core->gfx.fromPixelSize(
        core->input.mouse.x,
        core->input.mouse.y
    );
    mouse.h -= ((windowSize.h / 2) - .5);
    playerYTo = mouse.h - vOffset;
    if (playerYAt > 1) {
        playerYAt = 1;
    }

    // draw player
    ChompGfxRect rect;
    rect.x = (windowSize.w - playerSprite->size.w) / 2;
    rect.y = vOffset + playerYAt;
    rect.w = playerSprite->size.w;
    rect.h = playerSprite->size.h;
    core->gfx.addLayerToRenderer(playerSprite, NULL, &rect);

    // draw walls
    rect.w = wallSprite->size.w;
    rect.h = wallSprite->size.h;
    for (uint16_t x = 0; x < walls.size(); x++) {
        if (x * WALL_SPACING < playerX) {
            continue;
        }
        for (uint16_t y = 0; y < walls[x].size(); y++) {
            if (!walls[x][y]) {
                continue;
            }
            rect.x = (x * WALL_SPACING) - playerX;
            rect.y = vOffset + (y * wallSprite->size.h);
            core->gfx.addLayerToRenderer(wallSprite, NULL, &rect);
        }
    }
    
    // move player
    playerX += speed * core->deltaTime;

    // draw score
    rect.x = .01;
    rect.y = .01;
    rect.w = scoreText->size.w;
    rect.h = scoreText->size.h;
    core->gfx.addLayerToRenderer(scoreText, NULL, &rect);

    // next round
    if (playerX > (WALL_SPACING * WALLS_PER_ROUND) + 3) {
        startRound();
    }
}

void ChompyStatePlay::startRound()
{
    round += 1;
    if (round % SPEED_UP_RATE == 0) {
        speed = speed * ROUND_SPEED_MOD;
        if (speed > MAX_SPEED) {
            speed = MAX_SPEED;
        }
        std::cout << speed << std::endl;
    }
    playerX = -2;
    walls.clear();
    for (uint16_t i = 0; i < WALLS_PER_ROUND; i++) {
        generateWall();
    }
}

void ChompyStatePlay::generateWall()
{
    std::vector<bool> wall;
    uint16_t wallVerCount = 1.0 / wallSprite->size.h;
    uint16_t gapPos = rand() % (wallVerCount - WALL_V_GAP) + 1;
    for (uint16_t i = 0; i < wallVerCount; i++) {
        if (i >= gapPos && i < gapPos + WALL_V_GAP) {
            wall.push_back(false);
        } else {
            wall.push_back(true);
        }
    }
    walls.push_back(wall);
}