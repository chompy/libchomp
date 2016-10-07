#ifndef CHOMP_INPUT_MOUSE_H
#define CHOMP_INPUT_MOUSE_H

#include <SDL2/SDL.h>
#include <vector>
#include "../gfx/structs.h"
#include "mouse.h"

#define MOUSE_BUTTON_LEFT SDL_BUTTON_LEFT
#define MOUSE_BUTTON_MIDDLE SDL_BUTTON_MIDDLE
#define MOUSE_BUTTON_RIGHT SDL_BUTTON_RIGHT
#define MOUSE_BUTTON_X1 SDL_BUTTON_X1
#define MOUSE_BUTTON_X2 SDL_BUTTON_X2

class ChompInputMouse
{
public:

    ChompInputMouse();
    ~ChompInputMouse();

    int32_t x, y, xrel, yrel;

    bool pressed(uint8_t button);
    bool in(int32_t pixelX, int32_t pixelY, int32_t pixelW, int32_t pixelH);
    //bool in(ChompGfxRect* rect);

    void event(SDL_Event* event);

private:

    std::vector<uint8_t> buttons;

};

#endif