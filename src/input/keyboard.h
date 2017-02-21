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