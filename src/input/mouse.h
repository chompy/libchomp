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

#ifndef CHOMP_INPUT_MOUSE_H
#define CHOMP_INPUT_MOUSE_H

#include <vector>
#include "../sdl_includes.h"
#include "../gfx/structs.h"

#define CHOMP_INPUT_MOUSE_BUTTON_LEFT SDL_BUTTON_LEFT
#define CHOMP_INPUT_MOUSE_BUTTON_MIDDLE SDL_BUTTON_MIDDLE
#define CHOMP_INPUT_MOUSE_BUTTON_RIGHT SDL_BUTTON_RIGHT
#define CHOMP_INPUT_MOUSE_BUTTON_X1 SDL_BUTTON_X1
#define CHOMP_INPUT_MOUSE_BUTTON_X2 SDL_BUTTON_X2

namespace Chomp
{

    /**
     * Mouse input class.
     */
    class InputMouse
    {
    public:

        /**
         * Constructor.
         */
        InputMouse();

        /**
         * Destructor.
         */
        ~InputMouse();

        /**
         * Pixel x position of mouse.
         */
        int32_t x;

        /**
         * Pixel y position of mouse.
         */
        int32_t y;

        /**
         * Mouse relative x motion.
         */
        int32_t xrel;

        /**
         * Mouse relative y motion.
         */
        int32_t yrel;

        /**
         * Check pressed state of given button.
         * @param button Button (MOUSE_BUTTON_LEFT|MOUSE_BUTTON_MIDDLE|MOUSE_BUTTON_RIGHT|MOUSE_BUTTON_X1|MOUSE_BUTTON_X2)
         * @return True if button pressed
         */
        bool pressed(uint8_t button);

        /**
         * Check if mouse pointer is in a given boundary.
         * @param pixelX Pixel x
         * @param pixelY Pixel y
         * @param pixelW Pixel width
         * @param pixelH Pixel height
         * Return True if mouse is in boundary
         */
        bool in(int32_t pixelX, int32_t pixelY, int32_t pixelW, int32_t pixelH);

        /**
         * Register mouse input event.
         * @param event SDL Event
         */
        void event(SDL_Event* event);

    private:

        /**
         * Vector containing all currently pressed
         * buttons.
         */
        std::vector<uint8_t> buttons;

    };
};

#endif