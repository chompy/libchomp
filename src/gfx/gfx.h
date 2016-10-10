#ifndef CHOMP_GFX_H
#define CHOMP_GFX_H

#ifndef ANDROID
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <vector>
#include <algorithm>
#include <stdint.h>
#include <string>
#include "../asset/asset.h"
#include "../asset/bitmap.h"
#include "structs.h"
#include "layer.h"
#include "sprite.h"
#include "../exception/sdl_exception.h"

#define DEFAULT_WINDOW_W 640
#define DEFAULT_WINDOW_H 480

struct RenderLayers {
    bool operator<(const RenderLayers &renderLayer) const { return renderLayer.layer->zIndex > layer->zIndex; }
    ChompGfxLayer* layer;
    ChompGfxRect srcRect;
    ChompGfxRect dstRect;
};

class ChompGfx
{
public:

    ChompGfx();
    ~ChompGfx();

    // window data
    ChompGfxSize getWindowSize();
    void setWindowPixelSize(const uint16_t width, const uint16_t height);

    // conversions
    void toPixelSize(ChompGfxSize* size, uint16_t* width, uint16_t* height);
    ChompGfxSize fromPixelSize(const uint16_t width, const uint16_t height);

    // camera
    ChompGfxPosition getCameraPosition();
    void setCameraPosition(ChompGfxPosition* position);

    // general draw
    void setDrawColor(ChompGfxColor* color);

    // layer management
    ChompGfxLayer* newLayer(const uint16_t pixelWidth, const uint16_t pixelHeight, ChompGfxSize* size);
    ChompGfxLayer* newLayerFromBitmap(uint8_t* bitmap, const uint16_t frame, ChompGfxSize* size);
    ChompGfxSprite* newSprite(const char* spriteName, ChompGfxSize* size);

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