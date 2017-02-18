#ifndef CHOMP_INPUT_KEYBOARD_H
#define CHOMP_INPUT_KEYBOARD_H

#include <vector>
#include "../sdl_includes.h"
#include "../exception/sdl_exception.h"
#include <iostream>

namespace Chomp
{

    /**
     * Keyboard input class.
     */
    class InputKeyboard
    {
    public:

        /**
         * Constructor.
         */
        InputKeyboard();

        /**
         * Destructor.
         */
        ~InputKeyboard();

        /**
         * Check if key with given scancode is 
         * pressed.
         * @param scancode Key scancode
         * @return True if pressed
         * @see https://wiki.libsdl.org/SDLScancodeLookup
         */
        bool hasInput(uint16_t scancode);

        /**
         * Register keyboard input event.
         * @param event SDL Event
         */
        void event(SDL_Event* event);

    protected:

        /**
         * Vector containing currently active inputs.
         */
        std::vector<uint16_t> inputs;

    };
};

#endif