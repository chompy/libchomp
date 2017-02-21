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

#include "keyboard.h"

Chomp::InputKeyboard::InputKeyboard()
{
    inputs.clear();
}

Chomp::InputKeyboard::~InputKeyboard()
{
    inputs.clear();
}


bool Chomp::InputKeyboard::hasInput(uint16_t scancode)
{
    for (uint16_t i = 0; i < inputs.size(); i++) {
        if (inputs[i] == scancode) {
            return true;
        }
    }
    return false;
}

void Chomp::InputKeyboard::event(SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
        {
            if (hasInput(event->key.keysym.scancode)) {
                return;
            }
            inputs.push_back(event->key.keysym.scancode);
            break;
        }
        case SDL_KEYUP:
        {
            for (uint16_t i = 0; i < inputs.size(); i++) {
                if (inputs[i] == event->key.keysym.scancode) {
                    inputs.erase(inputs.begin() + i);
                    return;
                }
            }
            break;
        }
    }
}