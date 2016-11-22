#ifndef CHOMP_INPUT_MOUSE_H
#define CHOMP_INPUT_MOUSE_H

#include <vector>
#include "../sdl_includes.h"
#include "../gfx/structs.h"

#define MOUSE_BUTTON_LEFT SDL_BUTTON_LEFT
#define MOUSE_BUTTON_MIDDLE SDL_BUTTON_MIDDLE
#define MOUSE_BUTTON_RIGHT SDL_BUTTON_RIGHT
#define MOUSE_BUTTON_X1 SDL_BUTTON_X1
#define MOUSE_BUTTON_X2 SDL_BUTTON_X2

/**
 * Mouse input class.
 */
class ChompInputMouse
{
public:

    /**
     * Constructor.
     */
    ChompInputMouse();

    /**
     * Destructor.
     */
    ~ChompInputMouse();

    /**
     * Pixel x position of mouse.
     */
    int32_t x;

    /**
     * Pixel y position of mouse.
     */
    int32_t y;

    /**
     * Mouse relative x motion.
     */
    int32_t xrel;

    /**
     * Mouse relative y motion.
     */
    int32_t yrel;

    /**
     * Check pressed state of given button.
     * @param button Button (MOUSE_BUTTON_LEFT|MOUSE_BUTTON_MIDDLE|MOUSE_BUTTON_RIGHT|MOUSE_BUTTON_X1|MOUSE_BUTTON_X2)
     * @return True if button pressed
     */
    bool pressed(uint8_t button);

    /**
     * Check if mouse pointer is in a given boundary.
     * @param pixelX Pixel x
     * @param pixelY Pixel y
     * @param pixelW Pixel width
     * @param pixelH Pixel height
     * Return True if mouse is in boundary
     */
    bool in(int32_t pixelX, int32_t pixelY, int32_t pixelW, int32_t pixelH);

    /**
     * Register mouse input event.
     * @param event SDL Event
     */
    void event(SDL_Event* event);

private:

    /**
     * Vector containing all currently pressed
     * buttons.
     */
    std::vector<uint8_t> buttons;

};

#endif