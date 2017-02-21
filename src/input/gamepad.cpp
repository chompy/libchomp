/**
    This file is part of Libchomp.

    Libchomp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Libchomp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Libchomp.  If not, see <http://www.gnu.org/licenses/>.
**/

#include "gamepad.h"
const char* Chomp::InputGamepad::GAME_CONTROLLER_DATABASE_ASSET = "_gcdb";
uint32_t Chomp::InputGamepad::deviceIdCounter = 0;

Chomp::InputGamepad::InputGamepad()
{
    // init joystick/controller
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
            throw Chomp::SdlException();
            return;
        }
    }
    if (SDL_WasInit(SDL_INIT_GAMECONTROLLER) == 0) {
        if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
            throw Chomp::SdlException();
            return;
        }
    }
    // init asset handler
    Chomp::Asset asset;
    // load database
    if (asset.assetExists(Chomp::InputGamepad::GAME_CONTROLLER_DATABASE_ASSET)) {
        uint32_t dbSize = asset.getAssetSize(Chomp::InputGamepad::GAME_CONTROLLER_DATABASE_ASSET);
        uint8_t dbBuffer[dbSize];
        asset.readFile(
            Chomp::InputGamepad::GAME_CONTROLLER_DATABASE_ASSET,
            0,
            dbBuffer,
            dbSize
        );
        SDL_RWops* dbRW = SDL_RWFromMem(&dbBuffer, dbSize);
        SDL_GameControllerAddMappingsFromRW(dbRW, 1);
    }
    devices.clear();
    inputs.clear();
}

Chomp::InputGamepad::~InputGamepad()
{
    //closeAllDevices();
    inputs.clear();
}

void Chomp::InputGamepad::closeAllDevices()
{
    for (uint16_t i = 0; i < devices.size(); i++) {
        if (devices[i].gamepad) {
            SDL_GameControllerClose(devices[i].gamepad);
        }
    }
    devices.clear();    
}

Chomp::InputGamepadDevice* Chomp::InputGamepad::deviceFromId(uint32_t id)
{
    for (uint32_t i = 0; i < devices.size(); i++) {
        if (devices[i].id == id) {
            return &devices[i];
        }
    }
    return NULL;
}

Chomp::InputGamepadDevice* Chomp::InputGamepad::deviceFromInput(Chomp::InputGamepadInputData* input)
{
    if (!input) {
        return NULL;
    }
    return deviceFromId(input->deviceId);
}

Chomp::InputGamepadDevice* Chomp::InputGamepad::deviceFromIndex(uint32_t index)
{
    for (uint32_t i = 0; i < devices.size(); i++) {
        if (i == index) {
            return &devices[i];
        }
    }
    return NULL;
}

Chomp::InputGamepadDevice* Chomp::InputGamepad::deviceFromSdlGameController(SDL_GameController* gamepad)
{
    for (uint32_t i = 0; i < devices.size(); i++) {
        if (devices[i].gamepad == gamepad) {
            return &devices[i];
        }
    }
    return NULL;
}

std::vector<Chomp::InputGamepadDevice*> Chomp::InputGamepad::getDevicesWithInput(uint8_t input)
{
    std::vector<Chomp::InputGamepadDevice*> deviceInputList;
    deviceInputList.clear();
    for (uint32_t i = 0; i < inputs.size(); i++) {
        if (inputs[i].input == input && inputs[i].value != 0) {
            deviceInputList.push_back(
                deviceFromInput(&inputs[i])
            );
        }
    }
    return deviceInputList;
}

bool Chomp::InputGamepad::hasInput(Chomp::InputGamepadDevice* device, uint8_t input)
{
    if (!device) {
        return false;
    }
    for (uint32_t i = 0; i < inputs.size(); i++) {
        if (inputs[i].deviceId != device->id || inputs[i].input != input) {
            continue;
        }
        return inputs[i].value != 0;
    }
    return false;
}

bool Chomp::InputGamepad::hasInput(uint32_t index, uint8_t input)
{
    return hasInput(
        deviceFromIndex(index),
        input
    );
}


int16_t Chomp::InputGamepad::getInputValue(Chomp::InputGamepadDevice* device, uint8_t input)
{
    if (!device) {
        return 0;
    }
    for (uint32_t i = 0; i < inputs.size(); i++) {
        if (inputs[i].deviceId != device->id || inputs[i].input != input) {
            continue;
        }
        return inputs[i].value;
    }
    return 0;
}

int16_t Chomp::InputGamepad::getInputValue(uint32_t index, uint8_t input)
{
    return getInputValue(
        deviceFromIndex(index),
        input
    );
}

void Chomp::InputGamepad::event(SDL_Event* event)
{
    switch(event->type) {
        case SDL_CONTROLLERAXISMOTION:
        {
            // collect input data
            Chomp::InputGamepadDevice* device = deviceFromSdlGameController(
                SDL_GameControllerFromInstanceID(event->caxis.which)
            );
            if (!device || !device->gamepad) {
                return;
            }
            uint8_t axis = convertSdlAxis(event->caxis.axis);
            // find existing input
            for (uint32_t i = 0; i < inputs.size(); i++) {
                if (inputs[i].deviceId != device->id || inputs[i].input != axis) {
                    continue;
                }
                inputs[i].value = event->caxis.value;
                return;
            }
            // new input
            Chomp::InputGamepadInputData inputData;
            inputData.deviceId = device->id;
            inputData.input = axis; 
            inputData.value = event->caxis.value;
            inputs.push_back(inputData);
            break;
        }
        case SDL_CONTROLLERBUTTONDOWN:
        {
            // collect input data
            Chomp::InputGamepadDevice* device = deviceFromSdlGameController(
                SDL_GameControllerFromInstanceID(event->cbutton.which)
            );
            if (!device || !device->gamepad) {
                return;
            }
            uint8_t button = convertSdlButton(event->cbutton.button);
            // find existing input
            for (uint32_t i = 0; i < inputs.size(); i++) {
                if (inputs[i].deviceId != device->id || inputs[i].input != button) {
                    continue;
                }
                inputs[i].value = 1;
                return;
            }
            // new input
            Chomp::InputGamepadInputData inputData;
            inputData.deviceId = device->id;
            inputData.input = button; 
            inputData.value = 1;
            inputs.push_back(inputData);
            break;
        }
        case SDL_CONTROLLERBUTTONUP:
        {
            // collect input data
            Chomp::InputGamepadDevice* device = deviceFromSdlGameController(
                SDL_GameControllerFromInstanceID(event->cbutton.which)
            );
            if (!device || !device->gamepad) {
                return;
            }
            uint8_t button = convertSdlButton(event->cbutton.button);
            // find existing input
            for (uint32_t i = 0; i < inputs.size(); i++) {
                if (inputs[i].deviceId != device->id || inputs[i].input != button) {
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
                throw Chomp::SdlException();
            }
            Chomp::InputGamepad::deviceIdCounter += 1;
            Chomp::InputGamepadDevice device;
            device.id = Chomp::InputGamepad::deviceIdCounter;
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

uint8_t Chomp::InputGamepad::convertSdlButton(uint8_t sdlButton)
{
    switch (sdlButton)
    {
        case SDL_CONTROLLER_BUTTON_A:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_A;
            break;
        }
        case SDL_CONTROLLER_BUTTON_B:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_B;
            break;
        }
        case SDL_CONTROLLER_BUTTON_X:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_X;
            break;
        }
        case SDL_CONTROLLER_BUTTON_Y:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_Y;
            break;
        }
        case SDL_CONTROLLER_BUTTON_BACK:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_BACK;
            break;
        }
        case SDL_CONTROLLER_BUTTON_START:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_START;
            break;
        }
        case SDL_CONTROLLER_BUTTON_LEFTSTICK:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_LSTICK;
            break;
        }
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_RSTICK;
            break;
        }
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_LSHOULDER;
            break;
        }
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        {
            return CHOMP_INPUT_GAMEPAD_BTN_RSHOULDER;
            break;
        }
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
        {
            return CHOMP_INPUT_GAMEPAD_DPAD_U;
            break;
        }
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        {
            return CHOMP_INPUT_GAMEPAD_DPAD_D;
            break;
        }
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        {
            return CHOMP_INPUT_GAMEPAD_DPAD_L;
            break;
        }
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        {
            return CHOMP_INPUT_GAMEPAD_DPAD_R;
            break;
        }
    }
    return CHOMP_INPUT_GAMEPAD_INVALID;
}

uint8_t Chomp::InputGamepad::convertSdlAxis(uint8_t sdlAxis)
{
    switch (sdlAxis)
    {
        case SDL_CONTROLLER_AXIS_LEFTX:
        {
            return CHOMP_INPUT_GAMEPAD_AXIS_LX;
            break;
        }
        case SDL_CONTROLLER_AXIS_LEFTY:
        {
            return CHOMP_INPUT_GAMEPAD_AXIS_LY;
            break;
        }
        case SDL_CONTROLLER_AXIS_RIGHTX:
        {
            return CHOMP_INPUT_GAMEPAD_AXIS_RX;
            break;
        }
        case SDL_CONTROLLER_AXIS_RIGHTY:
        {
            return CHOMP_INPUT_GAMEPAD_AXIS_RY;
            break;
        }
        case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
        {
            return CHOMP_INPUT_GAMEPAD_AXIS_LTRIGGER;
            break;
        }
        case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
        {
            return CHOMP_INPUT_GAMEPAD_AXIS_RTRIGGER;
            break;
        }
    }
    return CHOMP_INPUT_GAMEPAD_INVALID;
}