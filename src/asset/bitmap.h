#ifndef CHOMP_ASSET_BITMAP_H
#define CHOMP_ASSET_BITMAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <string>

#define BITMAP_SIZE_W_POS 0
#define BITMAP_SIZE_H_POS 2
#define BITMAP_FRAMECOUNT_POS 4
#define BITMAP_DATA_POS 6

class ChompBitmap
{
public:

    static int16_t getWidth(uint8_t* bitmap);
    static int16_t getHeight(uint8_t* bitmap);
    static uint16_t getFrameCount(uint8_t* bitmap);
    static uint8_t* getFrame(uint8_t* bitmap, uint8_t frame);
    static uint8_t getAnimationFps(uint8_t* bitmap);
    static uint8_t* getAnimationData(uint8_t* bitmap);
    static SDL_Texture* getTexture(SDL_Renderer* renderer, uint8_t* bitmap, uint16_t frame);

};

#endif