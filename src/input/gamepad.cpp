#include "gamepad.h"
const char* ChompInputGamepad::GAME_CONTROLLER_DATABASE_ASSET = "_gcdb";
uint32_t ChompInputGamepad::deviceIdCounter = 0;

ChompInputGamepad::ChompInputGamepad()
{
    // init joystick/controller
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
            throw ChompSdlException();
            return;
        }
    }
    if (SDL_WasInit(SDL_INIT_GAMECONTROLLER) == 0) {
        if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
            throw ChompSdlException();
            return;
        }
    }

    // load database
    if (ChompAsset::assetExists(ChompInputGamepad::GAME_CONTROLLER_DATABASE_ASSET)) {
        uint32_t dbSize = ChompAsset::getAssetSize(ChompInputGamepad::GAME_CONTROLLER_DATABASE_ASSET);
        uint8_t dbBuffer[dbSize];
        ChompAsset::readFile(
            ChompInputGamepad::GAME_CONTROLLER_DATABASE_ASSET,
            0,
            dbBuffer,
            dbSize
        );
        SDL_RWops* dbRW = SDL_RWFromMem(&dbBuffer, dbSize);
        SDL_GameControllerAddMappingsFromRW(dbRW, 1);
    }

    // fetch gamepads
    devices.clear();
    inputs.clear();
    fetchDevices();
}

ChompInputGamepad::~ChompInputGamepad()
{
    //closeAllDevices();
    inputs.clear();
}

void ChompInputGamepad::closeAllDevices()
{
    for (uint16_t i = 0; i < devices.size(); i++) {
        if (devices[i].gamepad) {
            SDL_GameControllerClose(devices[i].gamepad);
        }
    }
    devices.clear();    
}

void ChompInputGamepad::fetchDevices()
{
    closeAllDevices();
    for (uint16_t i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            SDL_GameController* gamepad = SDL_GameControllerOpen(i);
            if (!gamepad) {
                throw ChompSdlException();
            }
            ChompInputGamepad::deviceIdCounter += 1;
            ChompInputGamepadDevice device;
            device.gamepad = gamepad;
            device.id = ChompInputGamepad::deviceIdCounter;
            devices.push_back(device);
        }
    }
}

ChompInputGamepadDevice ChompInputGamepad::deviceFromId(uint32_t id)
{
    for (uint32_t i = 0; i < devices.size(); i++) {
        if (devices[i].id == id) {
            return devices[i];
        }
    }
    // empty device
    ChompInputGamepadDevice device;
    device.id = 0;
    device.gamepad = NULL;
    return device;
}

ChompInputGamepadDevice ChompInputGamepad::deviceFromInput(ChompInputGamepadInputData input)
{
    return deviceFromId(input.deviceId);
}

ChompInputGamepadDevice ChompInputGamepad::deviceFromIndex(uint32_t index)
{
    for (uint32_t i = 0; i < devices.size(); i++) {
        if (i == index) {
            return devices[i];
        }
    }
    // empty device
    ChompInputGamepadDevice device;
    device.id = 0;
    device.gamepad = NULL;
    return device;
}

ChompInputGamepadDevice ChompInputGamepad::deviceFromSdlGameController(SDL_GameController* gamepad)
{
    for (uint32_t i = 0; i < devices.size(); i++) {
        if (devices[i].gamepad == gamepad) {
            return devices[i];
        }
    }
    // empty device
    ChompInputGamepadDevice device;
    device.id = 0;
    device.gamepad = NULL;
    return device;
}

std::vector<ChompInputGamepadDevice> ChompInputGamepad::getDevicesWithInput(uint8_t input)
{
    std::vector<ChompInputGamepadDevice> deviceInputList;
    deviceInputList.clear();
    for (uint32_t i = 0; i < inputs.size(); i++) {
        if (inputs[i].input == input) {
            deviceInputList.push_back(
                deviceFromInput(inputs[i])
            );
        }
    }
    return deviceInputList;
}

bool ChompInputGamepad::hasInput(ChompInputGamepadDevice device, uint8_t input)
{
    for (uint32_t i = 0; i < inputs.size(); i++) {
        if (inputs[i].deviceId != device.id || inputs[i].input != input) {
            continue;
        }
        return inputs[i].value != 0;
    }
    return false;
}

bool ChompInputGamepad::hasInput(uint32_t index, uint8_t input)
{
    return hasInput(
        deviceFromIndex(index),
        input
    );
}


int16_t ChompInputGamepad::getInputValue(ChompInputGamepadDevice device, uint8_t input)
{
    for (uint32_t i = 0; i < inputs.size(); i++) {
        if (inputs[i].deviceId != device.id || inputs[i].input != input) {
            continue;
        }
        return inputs[i].value;
    }
    return 0;
}

int16_t ChompInputGamepad::getInputValue(uint32_t index, uint8_t input)
{
    return getInputValue(
        deviceFromIndex(index),
        input
    );
}

void ChompInputGamepad::event(SDL_Event* event)
{
    switch(event->type) {
        case SDL_CONTROLLERAXISMOTION:
        {
            // collect input data
            ChompInputGamepadDevice device = deviceFromSdlGameController(
                SDL_GameControllerFromInstanceID(event->caxis.which)
            );
            if (!device.gamepad) {
                return;
            }
            uint8_t axis = convertSdlAxis(event->caxis.axis);
            // find existing input
            for (uint32_t i = 0; i < inputs.size(); i++) {
                if (inputs[i].deviceId != device.id || inputs[i].input != axis) {
                    continue;
                }
                inputs[i].value = event->caxis.value;
                return;
            }
            // new input
            ChompInputGamepadInputData inputData;
            inputData.deviceId = device.id;
            inputData.input = axis; 
            inputData.value = event->caxis.value;
            inputs.push_back(inputData);
            break;
        }
        case SDL_CONTROLLERBUTTONDOWN:
        {
            // collect input data
            ChompInputGamepadDevice device = deviceFromSdlGameController(
                SDL_GameControllerFromInstanceID(event->cbutton.which)
            );
            if (!device.gamepad) {
                return;
            }
            uint8_t button = convertSdlButton(event->cbutton.button);
            // find existing input
            for (uint32_t i = 0; i < inputs.size(); i++) {
                if (inputs[i].deviceId != device.id || inputs[i].input != button) {
                    continue;
                }
                inputs[i].value = 1;
                return;
            }
            // new input
            ChompInputGamepadInputData inputData;
            inputData.deviceId = device.id;
            inputData.input = button; 
            inputData.value = 1;
            inputs.push_back(inputData);
            break;
        }
        case SDL_CONTROLLERBUTTONUP:
        {
            // collect input data
            ChompInputGamepadDevice device = deviceFromSdlGameController(
                SDL_GameControllerFromInstanceID(event->cbutton.which)
            );
            if (!device.gamepad) {
                return;
            }
            uint8_t button = convertSdlButton(event->cbutton.button);
            // find existing input
            for (uint32_t i = 0; i < inputs.size(); i++) {
                if (inputs[i].deviceId != device.id || inputs[i].input != button) {
                    continue;
                }
                inputs[i].value = 0;
                return;
            }
            break;
        }
        case SDL_CONTROLLERDEVICEADDED:
        {
            SDL_GameController* gamepad = SDL_GameControllerOpen(event->cdevice.which);   
            if (!gamepad) {
                throw ChompSdlException();
            }
            ChompInputGamepad::deviceIdCounter += 1;
            ChompInputGamepadDevice device;
            device.id = ChompInputGamepad::deviceIdCounter;
            device.gamepad = gamepad;
            devices.push_back(device);
            break;
        }
        case SDL_CONTROLLERDEVICEREMOVED:
        {
            SDL_GameController* gamepad = SDL_GameControllerFromInstanceID(event->cdevice.which);
            for (uint16_t i = 0; i < devices.size(); i++) {
                if (devices[i].gamepad == gamepad) {
                    devices.erase(devices.begin() + i);
                    break;
                }
            }
            SDL_GameControllerClose(gamepad);
            gamepad = NULL;
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

uint8_t ChompInputGamepad::convertSdlAxis(uint8_t sdlAxis)
{
    switch (sdlAxis)
    {
        case SDL_CONTROLLER_AXIS_LEFTX:
        {
            return GAMEPAD_INPUT_AXIS_LX;
            break;
        }
        case SDL_CONTROLLER_AXIS_LEFTY:
        {
            return GAMEPAD_INPUT_AXIS_LY;
            break;
        }
        case SDL_CONTROLLER_AXIS_RIGHTX:
        {
            return GAMEPAD_INPUT_AXIS_RX;
            break;
        }
        case SDL_CONTROLLER_AXIS_RIGHTY:
        {
            return GAMEPAD_INPUT_AXIS_RY;
            break;
        }
        case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
        {
            return GAMEPAD_INPUT_AXIS_LTRIGGER;
            break;
        }
        case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
        {
            return GAMEPAD_INPUT_AXIS_RTRIGGER;
            break;
        }
    }
    return GAMEPAD_INPUT_INVALID;
}