#ifndef CHOMP_INPUT_H
#define CHOMP_INPUT_H

#include "../sdl_includes.h"
#include "../exception/sdl_exception.h"
#include "mouse.h"
#include "gamepad.h"
#include "keyboard.h"

namespace Chomp
{

    /**
     * Base class for handling inputs.
     */
    class Input
    {
    public:

        /**
         * Handles mouse inputs.
         */
        Chomp::InputMouse mouse;

        /**
         * Handles gamepad inputs.
         */
        Chomp::InputGamepad gamepad;

        /**
         * Handles keyboard inputs.
         */
        Chomp::InputKeyboard keyboard;

        /**
         * Constructor.
         */
        Input();

        /**
         * Destructor.
         */
        ~Input();

        /**
         * Register input event.
         * @param event SDL Event
         */
        void event(SDL_Event* event);

    };
};

#endif