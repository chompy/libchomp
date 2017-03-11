#include "state_play.h"

void ChompyStatePlay::enter()
{

    // config
    Chomp::Config config("game");
    wallSpacing = config.getFloat("wall.spacing", WALL_SPACING);
    wallGap = config.getInt("wall.gap", WALL_V_GAP);
    wallsPerRound = config.getInt("wall.round_count", WALLS_PER_ROUND);
    playerVerticalSpeed = config.getFloat("player.v_speed", VER_MOVE_INC);
    playerMaxSpeed = config.getFloat("player.h_max_speed", MAX_SPEED);
    playerAccelRate = config.getFloat("player.h_accel_rate", SPEED_ACCEL);
    playerBounce = config.getFloat("player.h_bounce", BOUNCE_SPEED);

    // seed random
    srand (time(NULL));
    // hide cursor
    core->gfx.setCursorVisibility(false);
    // game layer
    Chomp::GfxSize size;
    size.w = GAME_AREA_W;
    size.h = GAME_AREA_H;
    gameLayer = core->gfx.newLayer(GAME_AREA_W * 1024, GAME_AREA_H * 1024, &size);

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
    scoreText = core->gfx.newTextLayer("normal", 24, &size);
    // center player
    Chomp::GfxSize windowSize = core->gfx.getWindowSize();
    playerYTo = (windowSize.h - playerSprite->size.h) / 2;
    playerPos.x = 0;
    playerPos.y = playerYTo;
    speed = 0;

    // start first round
    lives = config.getInt("player.lives", START_LIVES);
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
    Chomp::GfxColor color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    core->gfx.setDrawColor(&color);
    gameLayer->fill();

    // current window size
    Chomp::GfxSize windowSize = core->gfx.getWindowSize();

    // speed accel
    speed += playerAccelRate * core->deltaTime;
    if (speed > playerMaxSpeed) {
        speed = playerMaxSpeed;
    }

    // animation
    if (speed <= 0) {
        playerSprite->setAnimation("stop");
    } else {
        playerSprite->setAnimation("move");
    }

    // movement
    if (playerPos.y > playerYTo) {
        playerPos.y -= (playerVerticalSpeed * core->deltaTime);
    } else if (playerPos.y < playerYTo) {
        playerPos.y += (playerVerticalSpeed * core->deltaTime);
    }
    if (fabs(playerPos.y - playerYTo) < playerVerticalSpeed * 2) {
        playerPos.y = playerYTo;
    }
    if (playerPos.y < 0) {
        playerPos.y = 0;
    } else if (playerPos.y > GAME_AREA_H - playerSprite->size.h) {
        playerPos.y = GAME_AREA_H - playerSprite->size.h;
    }

    if (core->input.mouse.pressed(CHOMP_INPUT_MOUSE_BUTTON_LEFT)) {
        inputDevice = INPUT_MOUSE;
    }
    if (core->input.keyboard.hasInput(SDL_SCANCODE_UP)) {
        playerYTo -= VER_MOVE_INC;
        inputDevice = INPUT_KEYBOARD;
    } else if (core->input.keyboard.hasInput(SDL_SCANCODE_DOWN)) {
        playerYTo += VER_MOVE_INC;
        inputDevice = INPUT_KEYBOARD;
    }
    if (core->input.gamepad.getDevicesWithInput(CHOMP_INPUT_GAMEPAD_DPAD_U).size() > 0) {
        playerYTo -= VER_MOVE_INC;
        inputDevice = INPUT_GAMEPAD;
    } else if (core->input.gamepad.getDevicesWithInput(CHOMP_INPUT_GAMEPAD_DPAD_D).size() > 0) {
        playerYTo += VER_MOVE_INC;
        inputDevice = INPUT_GAMEPAD;
    }
    if (inputDevice == INPUT_MOUSE) {
        Chomp::GfxSize mouse = core->gfx.fromPixelSize(
            core->input.mouse.x,
            core->input.mouse.y
        );
        mouse.h -= ((windowSize.h / 2) - .5);
        playerYTo = mouse.h;
    }
    if (playerYTo < 0) {
        playerYTo = 0;
    } else if (playerYTo > GAME_AREA_H - playerSprite->size.h) {
        playerYTo = GAME_AREA_H - playerSprite->size.h;
    }
    if (playerPos.y > GAME_AREA_H - playerSprite->size.h) {
        playerPos.y = GAME_AREA_H - playerSprite->size.h;
    }
    playerPos.x += speed * core->deltaTime;

    // draw walls
    Chomp::GfxRect rect;
    rect.w = wallSprite->size.w;
    rect.h = wallSprite->size.h;
    for (uint16_t x = 0; x < walls.size(); x++) {
        if (playerPos.x > x * wallSpacing) {
            continue;
        }
        for (uint16_t y = 0; y < walls[x].size(); y++) {
            if (!walls[x][y]) {
                continue;
            }
            rect.x = (x * wallSpacing) - playerPos.x;
            rect.y = y * wallSprite->size.h;
            gameLayer->drawLayer(wallSprite, NULL, &rect);
        }
        // wall collisions
        if (lastScoreX >= x + 1) {
            continue;
        }
        Chomp::GfxRect wallRect;
        wallRect.x = ((float) x * wallSpacing);
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
                    speed = -playerBounce;
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
    if (playerPos.x > (wallSpacing * wallsPerRound) + 3) {
        startRound();
    }
}

void ChompyStatePlay::startRound()
{
    lastScoreX = 0;
    round += 1;
    Chomp::GfxSize windowSize = core->gfx.getWindowSize();
    playerPos.x = -windowSize.w * 1.5;
    walls.clear();
    for (uint16_t i = 0; i < wallsPerRound; i++) {
        generateWall();
    }
}

void ChompyStatePlay::generateWall()
{
    std::vector<bool> wall;
    uint16_t wallVerCount = 1.0 / wallSprite->size.h;
    uint16_t gapPos = rand() % (wallVerCount - wallGap) + 1;
    for (uint16_t i = 0; i < wallVerCount; i++) {
        if (i >= gapPos && i < gapPos + wallGap) {
            wall.push_back(false);
        } else {
            wall.push_back(true);
        }
    }
    walls.push_back(wall);
}

void ChompyStatePlay::updateScore()
{
    Chomp::GfxColor color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    core->gfx.setDrawColor(&color);
    char scoreTextStr[24];
    sprintf(scoreTextStr, "%d", score);
    scoreText->setText(scoreTextStr, CHOMP_GFX_TEXT_RIGHT);
}