#ifndef CHOMP_INPUT_H
#define CHOMP_INPUT_H

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "../exception/sdl_exception.h"
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