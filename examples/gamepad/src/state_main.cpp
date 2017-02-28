#include "state_main.h"

const char* ChompyStateMain::ACTIVE_GAMEPAD_COUNT_STRING = "Connected Gamepads: %d";
const char* ChompyStateMain::ACTIVE_GAMEPAD_INPUT_STRING = "Device %d - Input %d (%d)";

void ChompyStateMain::enter()
{

    // set to high number so it resets
    activeGamepadCount = 9999;

    // last active input update
    lastInputUpdate = 0;

    // create active gamepad count text
    if (!activeGamepadCountText) {
        Chomp::GfxSize textLayerSize;
        textLayerSize.w = .75;
        textLayerSize.h = .1;
        activeGamepadCountText = core->gfx.newTextLayer("ariali", 24, &textLayerSize);
        activeGamepadCountText->setDrawMode(CHOMP_GFX_TEXT_DRAW_MODE_BLENDED);
    }
    // create active input text
    if (!activeInputText) {
        Chomp::GfxSize textLayerSize;
        textLayerSize.w = 1.0;
        textLayerSize.h = .85;
        activeInputText = core->gfx.newTextLayer("ariali", 18, &textLayerSize);
        activeInputText->setDrawMode(CHOMP_GFX_TEXT_DRAW_MODE_BLENDED);
    }

}

void ChompyStateMain::exit()
{
    if (activeGamepadCountText) {
        delete activeGamepadCountText;
    }
    if (activeInputText) {
        delete activeInputText;
    }
}

void ChompyStateMain::update()
{

    setActiveGamepadCountText();
    setActiveInputText();

    Chomp::GfxRect dstRect;
    dstRect.x = .1;
    dstRect.y = .1;
    dstRect.w = activeGamepadCountText->size.w;
    dstRect.h = activeGamepadCountText->size.h;
    core->gfx.addLayerToRenderer(activeGamepadCountText, NULL, &dstRect);
    dstRect.y = .25;
    dstRect.w = activeInputText->size.w;
    dstRect.h = activeInputText->size.h;
    core->gfx.addLayerToRenderer(activeInputText, NULL, &dstRect);
}

void ChompyStateMain::setActiveGamepadCountText()
{
    uint16_t currentActiveGamepadCount = core->input.gamepad.activeDeviceCount();
    if (currentActiveGamepadCount == activeGamepadCount) {
        return;
    }
    activeGamepadCount = currentActiveGamepadCount;
    char activeGamepadCountString[strlen(ChompyStateMain::ACTIVE_GAMEPAD_COUNT_STRING + 2)];
    sprintf(
        activeGamepadCountString,
        ChompyStateMain::ACTIVE_GAMEPAD_COUNT_STRING,
        activeGamepadCount
    );
    activeGamepadCountText->setText(
        activeGamepadCountString,
        CHOMP_GFX_TEXT_LEFT,
        CHOMP_GFX_TEXT_MIDDLE
    );
}

void ChompyStateMain::setActiveInputText()
{
    if (lastInputUpdate + INPUT_UPDATE_RATE > core->getTicks()) {
        return;
    }

    std::string inputString = "";
    uint16_t activeGamepadInputStringLen = strlen(ChompyStateMain::ACTIVE_GAMEPAD_INPUT_STRING);
    for (uint8_t i = 0; i < 32; i++) {
        std::vector<Chomp::InputGamepadDevice*> devices = core->input.gamepad.getDevicesWithInput(i);
        for (uint16_t j = 0; j < devices.size(); j++) {
            if (!devices[j] || devices[j]->id == 0) {
                continue;
            }
            char activeGamepadInputString[activeGamepadInputStringLen + 6];
            sprintf(
                activeGamepadInputString,
                ChompyStateMain::ACTIVE_GAMEPAD_INPUT_STRING,
                devices[j]->id,
                i,
                core->input.gamepad.getInputValue(devices[j], i)
            );
            if (!inputString.empty()) {
                inputString += "\n";
            }
            inputString += activeGamepadInputString;
        }
    }
    activeInputText->setText(
        inputString.c_str(),
        CHOMP_GFX_TEXT_LEFT,
        CHOMP_GFX_TEXT_TOP
    );
    lastInputUpdate = core->getTicks();
}