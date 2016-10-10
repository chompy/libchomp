#ifndef CHOMP_ASSET_BITMAP_H
#define CHOMP_ASSET_BITMAP_H

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#ifndef WITHOUT_SDL_IMAGE
#ifndef ANDROID
#include <SDL2/SDL_image.h>
#else
#include <SDL_image.h>
#endif
#endif

#include <stdint.h>
#include <string>
#include "../exception/sdl_exception.h"

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
    static uint8_t* getFrame(uint8_t* bitmap, const uint8_t frame);
    static uint8_t getAnimationFps(uint8_t* bitmap);
    static uint8_t* getAnimationData(uint8_t* bitmap);
    static SDL_Texture* getTexture(SDL_Renderer* renderer, uint8_t* bitmap, const uint16_t frame);

};

#endif