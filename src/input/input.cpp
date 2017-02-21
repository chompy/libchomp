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

#include "input.h"

Chomp::Input::Input()
{

}

Chomp::Input::~Input()
{
    
}

void Chomp::Input::event(SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            mouse.event(event);
            break;
        }

        case SDL_CONTROLLERAXISMOTION:
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        case SDL_CONTROLLERDEVICEADDED:
        case SDL_CONTROLLERDEVICEREMOVED:
        {
            gamepad.event(event);
            break;
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            keyboard.event(event);
            break;
        }
    }
}