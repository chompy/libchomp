#include "mouse.h"

ChompInputMouse::ChompInputMouse()
{
    x = 0;
    y = 0;
    xrel = 0;
    yrel = 0;
}

ChompInputMouse::~ChompInputMouse()
{

}

void ChompInputMouse::event(SDL_Event* event)
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

bool ChompInputMouse::pressed(uint8_t button)
{
    for (uint16_t i = 0; i < buttons.size(); i++) {
        if (buttons[i] == button) {
            return true;
        }
    }
    return false;
}

bool ChompInputMouse::in(int32_t pixelX, int32_t pixelY, int32_t pixelW, int32_t pixelH)
{
    return (
        x >= pixelX && x <= pixelX + pixelW &&
        y >= pixelY && y <= pixelY + pixelH
    );
}

/*bool ChompInputMouse::in(ChompGfxRect* rect)
{

}*/