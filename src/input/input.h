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