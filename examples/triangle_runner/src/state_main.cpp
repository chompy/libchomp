#include "state_main.h"

void ChompyStateMain::enter()
{

    Chomp::Config config("game");
    std::string langConfigName = "lang_" + config.getString("default_lang", "en");
    Chomp::Config langConfig(langConfigName.c_str());

    core->gfx.setCursorVisibility(true);
    Chomp::GfxSize size;
    size.w = 1.0;
    size.h = .49;
    titleText = core->gfx.newTextLayer("title", 48, &size);
    titleText->setText(langConfig.getString("title", "Test Game").c_str(), CHOMP_GFX_TEXT_CENTER);
    // if exact same size as above glitch occurs?? @TODO
    size.h = .499;
    flavorText = core->gfx.newTextLayer("normal", 24, &size);
    flavorText->setText(langConfig.getString("flavor").c_str(), CHOMP_GFX_TEXT_CENTER);
    size.h = .5;
    startText = core->gfx.newTextLayer("normal", 24, &size);
    startText->setText(langConfig.getString("start").c_str(), CHOMP_GFX_TEXT_CENTER);

}

void ChompyStateMain::exit()
{
    if (titleText) {
        delete titleText;
    }
    if (flavorText) {
        delete flavorText;
    }
    if (startText) {
        delete startText;
    }
}

void ChompyStateMain::update()
{

    // mouse press
    if (
        core->input.mouse.pressed(CHOMP_INPUT_MOUSE_BUTTON_LEFT) ||
        core->input.keyboard.hasInput(SDL_SCANCODE_SPACE) ||
        core->input.gamepad.getDevicesWithInput(CHOMP_INPUT_GAMEPAD_BTN_A).size() > 0
    ) {
        Chomp::State::changeState(playState);
        return;
    }

    // current window size
    Chomp::GfxSize windowSize = core->gfx.getWindowSize();

    // draw title text
    Chomp::GfxRect rect;
    rect.x = ( windowSize.w / 2 ) - ( titleText->size.w / 2);
    rect.y = .1;
    rect.w = titleText->size.w;
    rect.h = titleText->size.h;
    core->gfx.addLayerToRenderer(titleText, NULL, &rect);

    // draw flavor text
    rect.x = ( windowSize.w / 2 ) - ( flavorText->size.w / 2);
    rect.y = .3;
    rect.w = flavorText->size.w;
    rect.h = flavorText->size.h;
    core->gfx.addLayerToRenderer(flavorText, NULL, &rect);

    // draw start text
    rect.x = ( windowSize.w / 2 ) - ( startText->size.w / 2);
    rect.y = windowSize.h - .15;
    rect.w = startText->size.w;
    rect.h = startText->size.h;
    core->gfx.addLayerToRenderer(startText, NULL, &rect);

}