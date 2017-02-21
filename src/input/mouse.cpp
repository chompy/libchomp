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

#include "mouse.h"

Chomp::InputMouse::InputMouse()
{
    x = 0;
    y = 0;
    xrel = 0;
    yrel = 0;
}

Chomp::InputMouse::~InputMouse()
{

}

void Chomp::InputMouse::event(SDL_Event* event)
{
    switch(event->type) {
        case SDL_MOUSEMOTION:
        {
            x = event->motion.x;
            y = event->motion.y;
            xrel = event->motion.xrel;
            yrel = event->motion.yrel;
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            for (uint16_t i = 0; i < buttons.size(); i++) {
                if (buttons[i] == event->button.button) {
                    return;
                }
            }
            buttons.push_back(event->button.button);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            for (uint16_t i = 0; i < buttons.size(); i++) {
                if (buttons[i] == event->button.button) {
                    buttons.erase(buttons.begin() + i);
                    return;
                }
            }
            break;
        }
    }
}

bool Chomp::InputMouse::pressed(uint8_t button)
{
    for (uint16_t i = 0; i < buttons.size(); i++) {
        if (buttons[i] == button) {
            return true;
        }
    }
    return false;
}

bool Chomp::InputMouse::in(int32_t pixelX, int32_t pixelY, int32_t pixelW, int32_t pixelH)
{
    return (
        x >= pixelX && x <= pixelX + pixelW &&
        y >= pixelY && y <= pixelY + pixelH
    );
}

/*bool Chomp::InputMouse::in(ChompGfxRect* rect)
{

}*/