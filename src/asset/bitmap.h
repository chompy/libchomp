#ifndef CHOMP_ASSET_BITMAP_H
#define CHOMP_ASSET_BITMAP_H

#include <stdint.h>
#include <string>
#include "../sdl_includes.h"
#include "../exception/sdl_exception.h"

#define BITMAP_SIZE_W_POS 0
#define BITMAP_SIZE_H_POS 2
#define BITMAP_FRAMECOUNT_POS 4
#define BITMAP_DATA_POS 6

/**
 * Reads bitmap data from a byte array.
 */
class ChompBitmap
{
public:

    /**
     * Get width of bitmap.
     * @param bitmap Bitmap data
     * @return Width of bitmap
     */
    static int16_t getWidth(uint8_t* bitmap);

    /**
     * Get height of bitmap.
     * @param bitmap Bitmap data
     * @return Height of bitmap
     */
    static int16_t getHeight(uint8_t* bitmap);

    /**
     * Get number of frames in bitmap.
     * @param bitmap Bitmap data
     * @return Number of frames
     */
    static uint16_t getFrameCount(uint8_t* bitmap);

    /**
     * Get pointer to specific frame.
     * @param bitmap Bitmap data
     * @param frame Frame number
     * @return Pointer to frame
     */
    static uint8_t* getFrame(uint8_t* bitmap, const uint8_t frame);

    /**
     * Get FPS to play animatino back at.
     * @param bitmap Bitmap data
     * @return FPS
     */
    static uint8_t getAnimationFps(uint8_t* bitmap);

    /**
     * Get pointer to animation data.
     * @param bitmap Bitmap data.
     * @return Pointer to animation data
     */
    static uint8_t* getAnimationData(uint8_t* bitmap);

    /**
     * Convert given frame of given bitmap to SDL texture.
     * @param renderer SDL renderer
     * @param bitmap Bitmap data
     * @param frame Frame number
     * @return SDL Texture
     */
    static SDL_Texture* getTexture(SDL_Renderer* renderer, uint8_t* bitmap, const uint16_t frame);

};

#endif