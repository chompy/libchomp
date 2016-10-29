#include "state_play.h"

const char* ChompyStatePlay::PLAYER_ANIM_STOP = "stop";
const char* ChompyStatePlay::PLAYER_ANIM_MOVE = "move";
const char* ChompyStatePlay::PLAYER_ANIM_DIE = "die";

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
    playerSprite->zIndex = 2;
    // load wall sprite
    size.w = 0.04167;
    wallSprite = core->gfx.newSprite(
        "wall",
        &size
    );
    wallSprite->zIndex = 1;
    // load score text
    size.w = .4;
    scoreText = core->gfx.newTextLayer("tahoma", 24, &size);
    // center player
    ChompGfxSize windowSize = core->gfx.getWindowSize();
    playerYTo = (windowSize.h - playerSprite->size.h) / 2;
    playerPos.x = 0;
    playerPos.y = playerYTo;
    speed = START_SPEED;

    // start first round
    lives = START_LIVES;
    score = 0;
    round = 0;
    updateScore();
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

    // speed accel
    speed += SPEED_ACCEL * core->deltaTime;
    if (speed > maxSpeed) {
        speed = maxSpeed;
    }

    // animation
    if (speed <= 0) {
        playerSprite->setAnimation(ChompyStatePlay::PLAYER_ANIM_STOP);
    } else {
        playerSprite->setAnimation(ChompyStatePlay::PLAYER_ANIM_MOVE);
    }

    // movement
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
    playerPos.x += speed * core->deltaTime;

    // draw walls
    ChompGfxRect rect;
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
        // wall collisions
        if (lastScoreX >= x + 1) {
            continue;
        }
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
                    speed = -START_SPEED;
                    lastScoreX = x + 1;
                    break;
                }                
            }
            // didn't get hit, increase score
            if (lastScoreX < x + 1) {
                lastScoreX = x + 1;
                score += SCORE_PER_WALL;
                updateScore();
            }
        }
    }

    // draw player
    rect.x = 0;
    rect.y = playerPos.y;
    rect.w = playerSprite->size.w;
    rect.h = playerSprite->size.h;
    gameLayer->drawLayer(playerSprite, NULL, &rect);

    // draw score text
    rect.x = windowSize.w - scoreText->size.w - .01;
    rect.y = .01;
    rect.w = scoreText->size.w;
    rect.h = scoreText->size.h;
    core->gfx.addLayerToRenderer(scoreText, NULL, &rect);

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
    lastScoreX = 0;
    round += 1;
    maxSpeed = START_SPEED + (START_SPEED * (round * ROUND_SPEED_MOD) / SPEED_UP_RATE);
    if (maxSpeed > MAX_SPEED) {
        maxSpeed = MAX_SPEED;
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
    ChompGfxColor color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    core->gfx.setDrawColor(&color);
    char scoreTextStr[24];
    sprintf(scoreTextStr, "%d", score);
    scoreText->setText(scoreTextStr, TEXT_RIGHT);
}