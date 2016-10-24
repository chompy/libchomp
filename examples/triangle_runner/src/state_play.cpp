#include "state_play.h"

void ChompyStatePlay::enter()
{
    // seed random
    srand (time(NULL));
    // hide cursor
    core->gfx.setCursorVisibility(false);
    // game layer
    ChompGfxSize size;
    size.w = GAME_AREA_W;
    size.h = GAME_AREA_H;
    gameLayer = core->gfx.newLayer(1024, 1024, &size);

    // load player sprite
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
    //scoreText->setText("SCORE: 0");
    // center player
    ChompGfxSize windowSize = core->gfx.getWindowSize();
    playerYTo = (windowSize.h - playerSprite->size.h) / 2;
    playerPos.x = 0;
    playerPos.y = playerYTo;
    speed = START_SPEED;
    lastScoreTextUpdate = 0;

    // start first round
    score = 0;
    round = 0;
    startRound();
}

void ChompyStatePlay::exit()
{
    if (gameLayer) {
        delete gameLayer;
    }
    if (playerSprite) {
        delete playerSprite;
    }
    if (wallSprite) {
        delete wallSprite;
    }
    if (scoreText) {
        delete scoreText;
    }
    core->gfx.setCursorVisibility(true);
}

void ChompyStatePlay::update()
{

    // clear game layer
    ChompGfxColor color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    core->gfx.setDrawColor(&color);
    gameLayer->fill();

    // current window size
    ChompGfxSize windowSize = core->gfx.getWindowSize();

    // player movement
    if (playerPos.y > playerYTo) {
        playerPos.y -= (PLAYER_MOVE_INC * core->deltaTime);
    } else if (playerPos.y < playerYTo) {
        playerPos.y += (PLAYER_MOVE_INC * core->deltaTime);
    }
    if (fabs(playerPos.y - playerYTo) < PLAYER_MOVE_INC * 1.5) {
        playerPos.y = playerYTo;
    }
    if (playerPos.y < 0) {
        playerPos.y = 0;
    } else if (playerPos.y > GAME_AREA_H - playerSprite->size.h) {
        playerPos.y = GAME_AREA_H - playerSprite->size.h;
    }
    ChompGfxSize mouse = core->gfx.fromPixelSize(
        core->input.mouse.x,
        core->input.mouse.y
    );
    mouse.h -= ((windowSize.h / 2) - .5);
    playerYTo = mouse.h;
    if (playerPos.y > GAME_AREA_H - playerSprite->size.h) {
        playerPos.y = GAME_AREA_H - playerSprite->size.h;
    }

    // draw player
    ChompGfxRect rect;
    rect.x = 0;
    rect.y = playerPos.y;
    rect.w = playerSprite->size.w;
    rect.h = playerSprite->size.h;
    gameLayer->drawLayer(playerSprite, NULL, &rect);

    // draw walls
    rect.w = wallSprite->size.w;
    rect.h = wallSprite->size.h;
    for (uint16_t x = 0; x < walls.size(); x++) {
        if (playerPos.x > x * WALL_SPACING) {
            continue;
        }
        for (uint16_t y = 0; y < walls[x].size(); y++) {
            if (!walls[x][y]) {
                continue;
            }
            rect.x = (x * WALL_SPACING) - playerPos.x;
            rect.y = y * wallSprite->size.h;
            gameLayer->drawLayer(wallSprite, NULL, &rect);
        }

        // pass wall
        ChompGfxRect wallRect;
        wallRect.x = ((float) x * WALL_SPACING);
        wallRect.y = 0;
        wallRect.w = wallSprite->size.h;
        wallRect.h = GAME_AREA_H;
        if (
            playerSprite->hasCollision(
                &playerPos,
                &wallRect
            )
        ) {
            wallRect.h = wallSprite->size.h;
            for (uint16_t y = 0; y < walls[x].size(); y++) {
                if (!walls[x][y]) {
                    continue;
                }
                wallRect.y = y * wallSprite->size.h;
                if (
                    playerSprite->hasCollision(
                        &playerPos,
                        &wallRect
                    )
                ) {
                    std::cout << "COLLIDE" << std::endl;    
                }                
            }
        }

    }

    // move player
    playerPos.x += speed * core->deltaTime;
    score += 1;

    // update score text
    /*if (core->getTicks() - lastScoreTextUpdate > REDRAW_SCORE_RATE) {
        updateScore();
        lastScoreTextUpdate = core->getTicks();
    }
    rect.x = windowSize.w - scoreText->size.w - .01;
    rect.y = .01;
    rect.w = scoreText->size.w;
    rect.h = scoreText->size.h;
    core->gfx.addLayerToRenderer(scoreText, NULL, &rect);
    */

    // draw game layer
    rect.x = (windowSize.w / 2) - (GAME_AREA_W / 2);
    rect.y = (windowSize.h / 2) - (GAME_AREA_H / 2);
    rect.w = GAME_AREA_W;
    rect.h = GAME_AREA_H;
    core->gfx.addLayerToRenderer(gameLayer, NULL, &rect);

    // next round
    if (playerPos.x > (WALL_SPACING * WALLS_PER_ROUND) + 3) {
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
    }
    ChompGfxSize windowSize = core->gfx.getWindowSize();
    playerPos.x = -windowSize.w * 1.5;
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

void ChompyStatePlay::updateScore()
{
    return;
    char scoreTextStr[24];
    sprintf(scoreTextStr, "%d", score);
    scoreText->setText(scoreTextStr, TEXT_RIGHT);
}