#include "input.h"

ChompInput::ChompInput()
{

    // init joystic
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
            throw ChompSdlException();
            return;
        }
    }

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
    }
}