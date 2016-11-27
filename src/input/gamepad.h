#ifndef CHOMP_INPUT_GAMEPAD_H
#define CHOMP_INPUT_GAMEPAD_H

#include <vector>
#include "../sdl_includes.h"
#include "../exception/sdl_exception.h"
#include "../asset/asset.h"

#define GAMEPAD_INPUT_INVALID 99
#define GAMEPAD_INPUT_BTN_A 0
#define GAMEPAD_INPUT_BTN_B 1
#define GAMEPAD_INPUT_BTN_X 2
#define GAMEPAD_INPUT_BTN_Y 3
#define GAMEPAD_INPUT_BTN_BACK 4
#define GAMEPAD_INPUT_BTN_START 5
#define GAMEPAD_INPUT_BTN_LSHOULDER 6
#define GAMEPAD_INPUT_BTN_RSHOULDER 7
#define GAMEPAD_INPUT_BTN_LSTICK 8
#define GAMEPAD_INPUT_BTN_RSTICK 9
#define GAMEPAD_INPUT_DPAD_U 10
#define GAMEPAD_INPUT_DPAD_D 11
#define GAMEPAD_INPUT_DPAD_L 12
#define GAMEPAD_INPUT_DPAD_R 13
#define GAMEPAD_INPUT_AXIS_LX 14
#define GAMEPAD_INPUT_AXIS_LY 15
#define GAMEPAD_INPUT_AXIS_RX 16
#define GAMEPAD_INPUT_AXIS_RY 17
#define GAMEPAD_INPUT_AXIS_LTRIGGER 18
#define GAMEPAD_INPUT_AXIS_RTRIGGER 19

/**
 * Struct for storing details about a
 * specific device.
 */
struct ChompInputGamepadDevice
{
    uint32_t id; /**< Device id >*/
    SDL_GameController* gamepad; /**< Gamepad device >*/
};

/**
 * Struct for storing the value of a single
 * input. (Button, axis, etc?)
 */
struct ChompInputGamepadInputData
{
    uint32_t deviceId; /**< Device id >*/
    uint8_t input; /**< Input type >*/
    int16_t value; /**< Input value >*/
};

/**
 * Gamepad input class.
 */
class ChompInputGamepad
{
public:

    /**
     * Name of asset containing game controller database.
     */
    static const char* GAME_CONTROLLER_DATABASE_ASSET;

    /**
     * Constructor.
     */
    ChompInputGamepad();

    /**
     * Destructor.
     */
    ~ChompInputGamepad();

    /**
     * Get device info from id.
     * @param id Device id
     * @return Device info
     */
    ChompInputGamepadDevice deviceFromId(uint32_t id);

    /**
     * Get device info from input data.
     * @param input Input struct
     * @return Device info
     */
    ChompInputGamepadDevice deviceFromInput(ChompInputGamepadInputData input);

    /**
     * Get device info from index.
     * @param index Device index
     * @return Device info
     */
    ChompInputGamepadDevice deviceFromIndex(uint32_t index);

    /**
     * Get device info from SDL GameController.
     * @param gamepad SDL GameController
     * @return Device info
     */
    ChompInputGamepadDevice deviceFromSdlGameController(SDL_GameController* gamepad);

    /**
     * Get number of active devices.
     * @return Number of devices
     */
    uint32_t activeDeviceCount() { return devices.size(); }

    /**
     * Retrieve list of devices that have given
     * active input.
     * @param input Input id
     * @return Vector with device info
     */
    std::vector<ChompInputGamepadDevice> getDevicesWithInput(uint8_t input);

    /**
     * Check if given input is active on given device. (value != 0)
     * @param device Gamepad device
     * @param input Input id
     * @return True if input is active
     */
    bool hasInput(ChompInputGamepadDevice device, uint8_t input);

    /**
     * Check if given input is active on a device at the
     * given index.
     * @param index Device index
     * @param input Input id
     * @return True if input is active
     */
    bool hasInput(uint32_t index, uint8_t input);

    /**
     * Get value of input for given device.
     * @return device Gamepad device
     * @param input Input id
     * @return Value of input
     */
    int16_t getInputValue(ChompInputGamepadDevice device, uint8_t input);

    /**
     * Get value of input on a device at the given
     * index.
     * @param index Device index
     * @param input Input id
     * @return Value of input
     */
    int16_t getInputValue(uint32_t index, uint8_t input);

    /**
     * Register gamepad input event.
     * @param event SDL Event
     */
    void event(SDL_Event* event);

private:

    /**
     * Vector containing gamepad device info.
     */
    std::vector<ChompInputGamepadDevice> devices;

    /**
     * Vector containing current active inputs.
     */
    std::vector<ChompInputGamepadInputData> inputs;

    /**
     * Counter to increment with each new device so
     * that every device is ensured to have a unique
     * id.
     */
    static uint32_t deviceIdCounter;

    /**
     * Closes all open gamepads devices.
     */
    void closeAllDevices();

    /**
     * Convert SDL controller button to libchomp controller
     * input.
     * @param sdlButton SDL button
     * @return Libchomp button
     */
    uint8_t convertSdlButton(uint8_t sdlButton);

    /**
     * Convert SDL controller axis to libchomp controller
     * input.
     * @param sdlAxis SDL axis
     * @return Libchomp button
     */
    uint8_t convertSdlAxis(uint8_t sdlAxis);

};

#endif