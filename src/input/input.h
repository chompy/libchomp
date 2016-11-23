#ifndef CHOMP_INPUT_H
#define CHOMP_INPUT_H

#include "../sdl_includes.h"
#include "../exception/sdl_exception.h"
#include "mouse.h"
#include "gamepad.h"

/**
 * Base class for handling inputs.
 */
class ChompInput
{
public:

    /**
     * Handles mouse inputs.
     */
    ChompInputMouse mouse;

    /**
     * Handles gamepad inputs.
     */
    ChompInputGamepad gamepad;

    /**
     * @TODO Add Keyboard Here
     */

    /**
     * Constructor.
     */
    ChompInput();

    /**
     * Destructor.
     */
    ~ChompInput();

    /**
     * Register input event.
     * @param event SDL Event
     */
    void event(SDL_Event* event);

};

#endif