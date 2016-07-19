#ifndef CHOMP_GFX_WINDOW_H
#define CHOMP_GFX_WINDOW_H

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <string>
#include "../asset.h"
#include "../asset/bitmap.h"
#include "structs.h"
#include "layer.h"
#include "sprite.h"
#include "../exception.h"

#define DEFAULT_WINDOW_W 640
#define DEFAULT_WINDOW_H 480

struct RenderLayers {
    bool operator<(const RenderLayers &renderLayer) const { return renderLayer.layer->zIndex > layer->zIndex; }
    ChompGfxLayer* layer;
    ChompGfxRect srcRect;
    ChompGfxRect dstRect;
};

class ChompGfxWindow
{
public:

    ChompGfxWindow();
    ~ChompGfxWindow();

    // window data
    ChompGfxSize getWindowSize();
    void setWindowPixelSize(uint16_t width, uint16_t height);

    // conversions
    void toPixelSize(ChompGfxSize* size, uint16_t* width, uint16_t* height);
    ChompGfxSize fromPixelSize(uint16_t width, uint16_t height);

    // camera
    ChompGfxPosition getCameraPosition();
    void setCameraPosition(ChompGfxPosition* position);

    // general draw
    void setDrawColor(ChompGfxColor* color);

    // layer management
    ChompGfxLayer* newLayer(uint16_t pixelWidth, uint16_t pixelHeight, ChompGfxSize* size);
    ChompGfxLayer* newLayerFromBitmap(uint8_t* bitmap, uint16_t frame, ChompGfxSize* size);
    ChompGfxSprite* newSprite(char* spriteName, ChompGfxSize* size);

    // renderer
    void addLayerToRenderer(ChompGfxLayer* layer, ChompGfxRect* srcRect, ChompGfxRect* dstRect);
    void render();

protected:

    SDL_Window* window;
    SDL_Renderer* renderer;
    ChompGfxPosition camera;
    std::vector<RenderLayers> renderLayers;

};

#endif