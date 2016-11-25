#include "input.h"

ChompInput::ChompInput()
{

}

ChompInput::~ChompInput()
{
    
}

void ChompInput::event(SDL_Event* event)
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