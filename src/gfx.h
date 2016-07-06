#ifndef CHOMP_GFX_H
#define CHOMP_GFX_H

#include <SDL2/SDL.h>
#include <vector>
#include <stdint.h>
#include "asset/bitmap.h"

#define DEFAULT_WINDOW_W 640
#define DEFAULT_WINDOW_H 480
#define DEFAULT_CAMERA_Z 20

struct ChompGfxSize
{
    float w;
    float h;
};

struct ChompGfxPosition
{
    float x;
    float y;
    float z;
};

struct ChompGfxRect
{
    float x;
    float y;
    float w;
    float h;
};

struct ChompGfxColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

class ChompGfxLayer
{
public:

    ChompGfxLayer(SDL_Renderer* _renderer, SDL_Texture* _texture, ChompGfxSize* _size);
    ~ChompGfxLayer();

    // sdl texture
    SDL_Texture* texture;

    // size / position
    ChompGfxPosition position;
    ChompGfxSize size;    

    // general draw
    void drawLayer(ChompGfxLayer* layer, ChompGfxPosition* position, ChompGfxSize* size);

protected:

    SDL_Renderer* renderer;
    uint16_t pixelWidth, pixelHeight;

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
    ChompGfxLayer newLayer(uint16_t pixelWidth, uint16_t pixelHeight, ChompGfxSize* size);
    ChompGfxLayer newLayerFromBitmap(uint8_t* bitmap, uint16_t frame, ChompGfxSize* size);

    // renderer
    void addLayerToRenderer(ChompGfxLayer* layer);
    void render();

protected:

    SDL_Window* window;
    SDL_Renderer* renderer;
    ChompGfxPosition camera;
    std::vector<ChompGfxLayer*> renderLayers;

};

#endif