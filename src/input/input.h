#ifndef CHOMP_INPUT_H
#define CHOMP_INPUT_H

#include <SDL2/SDL.h>
#include "../exception.h"
#include "mouse.h"


class ChompInput
{
public:
    ChompInputMouse mouse;

    ChompInput();
    ~ChompInput();

    void event(SDL_Event* event);

};

#endif