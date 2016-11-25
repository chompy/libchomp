#include "keyboard.h"

ChompInputKeyboard::ChompInputKeyboard()
{
    inputs.clear();
}

ChompInputKeyboard::~ChompInputKeyboard()
{
    inputs.clear();
}


bool ChompInputKeyboard::hasInput(uint16_t scancode)
{
    for (uint16_t i = 0; i < inputs.size(); i++) {
        if (inputs[i] == scancode) {
            return true;
        }
    }
    return false;
}

void ChompInputKeyboard::event(SDL_Event* event)
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