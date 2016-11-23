#include "gamepad.h"

ChompInputGamepad::ChompInputGamepad()
{
    // init joystick
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
            throw ChompSdlException();
            return;
        }
    }
    // fetch gamepads
    gamepads.clear();
    inputs.clear();
    fetchGamepads();
}

ChompInputGamepad::~ChompInputGamepad()
{
    closeAllGamepads();
    inputs.clear();
}

void ChompInputGamepad::closeAllGamepads()
{
    for (uint16_t i = 0; i < gamepads.size(); i++) {
        if (gamepads[i]) {
            SDL_GameControllerClose(gamepads[i]);
        }
    }
    gamepads.clear();    
}

void ChompInputGamepad::fetchGamepads()
{
    closeAllGamepads();
    for (uint16_t i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            SDL_GameController* gamepad = SDL_GameControllerOpen(i);
            if (!gamepad) {
                throw ChompSdlException();
            }
            gamepads.push_back(gamepad);
        }
    }
}

void ChompInputGamepad::event(SDL_Event* event)
{
    switch(event->type) {
        case SDL_CONTROLLERAXISMOTION:
        {
            // @TODO
            break;
        }
        case SDL_CONTROLLERBUTTONDOWN:
        {
            // collect input data
            SDL_GameController* gamepad = SDL_GameControllerFromInstanceID(event->cbutton.which);
            uint8_t button = convertSdlButton(event->cbutton.button);
            // find existing input
            for (uint32_t i = 0; i < inputs.size(); i++) {
                if (inputs[i].gamepad != gamepad || inputs[i].input != button) {
                    continue;
                }
                inputs[i].value = 1;
                return;
            }
            // new input
            ChompInputGamepadInputData inputData;
            inputData.gamepad = gamepad;
            inputData.input = button; 
            inputData.value = 1;
            inputs.push_back(inputData);
            break;
        }
        case SDL_CONTROLLERBUTTONUP:
        {
            // collect input data
            SDL_GameController* gamepad = SDL_GameControllerFromInstanceID(event->cbutton.which);
            uint8_t button = convertSdlButton(event->cbutton.button);
            // find existing input
            for (uint32_t i = 0; i < inputs.size(); i++) {
                if (inputs[i].gamepad != gamepad || inputs[i].input != button) {
                    continue;
                }
                inputs[i].value = 0;
                return;
            }
            break;
        }
        case SDL_CONTROLLERDEVICEADDED:
        {
            SDL_GameController* controller = SDL_GameControllerOpen(event->cdevice.which);   
            if (!controller) {
                throw ChompSdlException();
            }
            gamepads.push_back(controller);
            break;
        }
        case SDL_CONTROLLERDEVICEREMOVED:
        {
            SDL_GameController* controller = SDL_GameControllerFromInstanceID(event->cdevice.which);
            for (uint16_t i = 0; i < gamepads.size(); i++) {
                if (gamepads[i] == controller) {
                    gamepads.erase(gamepads.begin() + i);
                    break;
                }
            }
            SDL_GameControllerClose(controller);
            controller = NULL;
            break;
        }
    }
}

uint8_t ChompInputGamepad::convertSdlButton(uint8_t sdlButton)
{
    switch (sdlButton)
    {
        case SDL_CONTROLLER_BUTTON_A:
        {
            return GAMEPAD_INPUT_BTN_A;
            break;
        }
        case SDL_CONTROLLER_BUTTON_B:
        {
            return GAMEPAD_INPUT_BTN_B;
            break;
        }
        case SDL_CONTROLLER_BUTTON_X:
        {
            return GAMEPAD_INPUT_BTN_X;
            break;
        }
        case SDL_CONTROLLER_BUTTON_Y:
        {
            return GAMEPAD_INPUT_BTN_Y;
            break;
        }
        case SDL_CONTROLLER_BUTTON_BACK:
        {
            return GAMEPAD_INPUT_BTN_BACK;
            break;
        }
        case SDL_CONTROLLER_BUTTON_START:
        {
            return GAMEPAD_INPUT_BTN_START;
            break;
        }
        case SDL_CONTROLLER_BUTTON_LEFTSTICK:
        {
            return GAMEPAD_INPUT_BTN_LSTICK;
            break;
        }
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
        {
            return GAMEPAD_INPUT_BTN_RSTICK;
            break;
        }
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        {
            return GAMEPAD_INPUT_BTN_LSHOULDER;
            break;
        }
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        {
            return GAMEPAD_INPUT_BTN_RSHOULDER;
            break;
        }
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
        {
            return GAMEPAD_INPUT_DPAD_U;
            break;
        }
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        {
            return GAMEPAD_INPUT_DPAD_D;
            break;
        }
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        {
            return GAMEPAD_INPUT_DPAD_L;
            break;
        }
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        {
            return GAMEPAD_INPUT_DPAD_R;
            break;
        }
    }
    return GAMEPAD_INPUT_INVALID;
}