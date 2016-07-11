#ifndef CHOMP_GFX_LAYER_H
#define CHOMP_GFX_LAYER_H

#include <SDL2/SDL.h>
#include "structs.h"

class ChompGfxLayer
{
public:

    ChompGfxLayer(SDL_Renderer* _renderer, SDL_Texture* _texture, ChompGfxSize* _size);
    ~ChompGfxLayer();

    // sdl texture
    SDL_Texture* texture;

    // size / position / rot
    ChompGfxPosition position;
    ChompGfxSize size;
    float rotation;
    uint8_t flip;

    // conversions
    void toPixelSize(ChompGfxSize* _size, uint16_t* width, uint16_t* height);
    ChompGfxSize fromPixelSize(uint16_t width, uint16_t height);
    uint16_t getPixelWidth() { return pixelWidth; }
    uint16_t getPixelHeight() { return pixelHeight; }
    uint16_t getPixelUnitWidth() { return pixelUnitWidth; }
    uint16_t getPixelUnitHeight() { return pixelUnitHeight; }

    // general draw
    void drawLayer(ChompGfxLayer* layer, ChompGfxRect* srcRect, ChompGfxRect* dstRect);
    
    static void drawLayerToLayer(SDL_Renderer* renderer, ChompGfxLayer* srcLayer, ChompGfxLayer* dstLayer, ChompGfxRect* srcRect, ChompGfxRect* dstRect);
    static void drawLayerToRenderTarget(SDL_Renderer* renderer, ChompGfxLayer* srcLayer, ChompGfxRect* srcRect, ChompGfxRect* dstRect, uint16_t targetUnitWidth, uint16_t targetUnitHeight);


protected:

    SDL_Renderer* renderer;
    uint16_t pixelWidth, pixelHeight;
    uint16_t pixelUnitWidth, pixelUnitHeight;

};

#endif