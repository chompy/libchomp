#ifndef CHOMP_INPUT_GAMEPAD_H
#define CHOMP_INPUT_GAMEPAD_H

#include <vector>
#include "../sdl_includes.h"
#include "../exception/sdl_exception.h"

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
 * Struct for storing the value of a single
 * input. (Button, axis, etc?)
 */
struct ChompInputGamepadInputData
{
    SDL_GameController* gamepad; /**< Gamepad device >*/
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
     * Constructor.
     */
    ChompInputGamepad();

    /**
     * Destructor.
     */
    ~ChompInputGamepad();


    //int16_t getInput(uint)


    /**
     * Register gamepad input event.
     * @param event SDL Event
     */
    void event(SDL_Event* event);

private:

    /**
     * Vector containing pointers to SDL Game Controllers
     */
    std::vector<SDL_GameController*> gamepads;

    /**
     * Vector containing current active inputs.
     */
    std::vector<ChompInputGamepadInputData> inputs;

    /**
     * Closes all open gamepads.
     */
    void closeAllGamepads();

    /**
     * Fetch all compatible and connected gamepads.
     */
    void fetchGamepads();

    /**
     * Convert SDL controller button to libchomp controller
     * button input.
     * @param sdlButton SDL button
     * @return Libchomp button
     */
    uint8_t convertSdlButton(uint8_t sdlButton);

};

#endif