#include "bitmap.h"

int16_t ChompBitmap::getWidth(uint8_t* bitmap)
{
    int16_t bitmapWidth = 0;
    if (!bitmap) {
        return bitmapWidth;
    }
    memcpy(&bitmapWidth, &bitmap[BITMAP_SIZE_W_POS], 2);
    return bitmapWidth;
}

int16_t ChompBitmap::getHeight(uint8_t* bitmap)
{
    int16_t bitmapHeight = 0;
    if (!bitmap) {
        return bitmapHeight;
    }
    memcpy(&bitmapHeight, &bitmap[BITMAP_SIZE_W_POS], 2);
    return bitmapHeight;
}

uint16_t ChompBitmap::getFrameCount(uint8_t* bitmap)
{
    uint16_t bitmapFrameCount = 0;
    if (!bitmap) {
        return bitmapFrameCount;
    }
    memcpy(&bitmapFrameCount, &bitmap[BITMAP_FRAMECOUNT_POS], 2);
    return bitmapFrameCount;
}

uint8_t* ChompBitmap::getFrame(uint8_t* bitmap, uint8_t frame)
{
    if (!bitmap) {
        return 0;
    }
    uint8_t* currentPos = &bitmap[BITMAP_DATA_POS];
    for (uint8_t i = 0; i < frame; i++) {
        uint32_t fileSize = 0;
        memcpy(&fileSize, &currentPos[0], 4);
        currentPos = &currentPos[4 + fileSize];
    }
    return currentPos;
}

uint8_t ChompBitmap::getAnimationFps(uint8_t* bitmap)
{
    uint8_t* animationData = ChompBitmap::getFrame(bitmap, ChompBitmap::getFrameCount(bitmap) + 1);
    return animationData[1];
}

uint8_t* ChompBitmap::getAnimationData(uint8_t* bitmap)
{
    if (!bitmap) {
        return nullptr;
    }
    return ChompBitmap::getFrame(bitmap, ChompBitmap::getFrameCount(bitmap) + 1);
}

SDL_Texture* ChompBitmap::getTexture(SDL_Renderer* renderer, uint8_t* bitmap, uint16_t frame)
{
    uint8_t* frameData = ChompBitmap::getFrame(bitmap, frame);
    uint32_t frameDataSize = 0;
    memcpy(&frameDataSize, &frameData[0], 4);
    SDL_RWops* frameDataRW = SDL_RWFromMem(&frameData[4], frameDataSize);
    if (!frameDataRW) {
        return nullptr;
    }
    SDL_Surface* surface = IMG_LoadPNG_RW(frameDataRW);
    if (!surface) {
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        renderer,
        surface
    );
    SDL_FreeSurface(surface);
    return texture;
}