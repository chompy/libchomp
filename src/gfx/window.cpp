#include "window.h"

ChompGfxWindow::ChompGfxWindow()
{

    // init sdl systems
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw ChompSdlInitException();
            return;
        }
    }
    
    // create window
    window = SDL_CreateWindow(
        "LibChomp Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        DEFAULT_WINDOW_W,
        DEFAULT_WINDOW_H,
        SDL_WINDOW_SHOWN |
        SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        throw ChompSdlInitException();
        return;
    }

    // create renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (!renderer) {
        throw ChompSdlInitException();
        return;
    }

    setCameraPosition(nullptr);
    setDrawColor(nullptr);

}

ChompGfxWindow::~ChompGfxWindow()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
}

ChompGfxSize ChompGfxWindow::getWindowSize()
{
    ChompGfxSize size;
    return size;
}

ChompGfxPosition ChompGfxWindow::getCameraPosition()
{
    return camera;
}

void ChompGfxWindow::toPixelSize(ChompGfxSize* size, uint16_t* width, uint16_t* height)
{
    int ww,wh;
    SDL_GetWindowSize(window, &ww, &wh);
    if (ww > wh) {
        *width = (uint16_t) abs( (size ? size->w : 1.0) * (float) wh );
        *height = (uint16_t) abs( (size ? size->h : 1.0) * (float) wh );
    } else {
        *width = (uint16_t) abs( (size ? size->w : 1.0) * (float) ww );
        *height = (uint16_t) abs( (size ? size->h : 1.0) * (float) ww );
    }
}

ChompGfxSize ChompGfxWindow::fromPixelSize(uint16_t width, uint16_t height)
{
    ChompGfxSize size;
    int ww,wh;
    SDL_GetWindowSize(window, &ww, &wh);    
    if (ww > wh) {
        size.w = width / (float) wh;
        size.h = height / (float) wh;
    } else {
        size.w = width / (float) ww;
        size.h = height / (float) ww;
    }
    return size;
}

void ChompGfxWindow::setCameraPosition(ChompGfxPosition* position)
{
    camera.x = position ? position->x : 0;
    camera.y = position ? position->y : 0;
}

void ChompGfxWindow::setDrawColor(ChompGfxColor* color)
{
    if (!renderer) {
        return;
    }
    SDL_SetRenderDrawColor(
        renderer,
        color ? color->r : 255,
        color ? color->g : 255,
        color ? color->b : 255,
        color ? color->a : 255
    );
}

ChompGfxLayer* ChompGfxWindow::newLayer(uint16_t pixelWidth, uint16_t pixelHeight, ChompGfxSize* size)
{
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        pixelWidth,
        pixelHeight
    );
    return new ChompGfxLayer(
        renderer,
        texture,
        size
    );
}

ChompGfxLayer* ChompGfxWindow::newLayerFromBitmap(uint8_t* bitmap, uint16_t frame, ChompGfxSize* size)
{
    if (!bitmap) {
        return newLayer(1, 1, size);
    }
    return new ChompGfxLayer(
        renderer,
        ChompBitmap::getTexture(renderer, bitmap, frame),
        size
    );
}

void ChompGfxWindow::addLayerToRenderer(ChompGfxLayer* layer, ChompGfxRect* srcRect, ChompGfxRect* dstRect)
{
    if (!layer) {
        return;
    }
    RenderLayers renderLayer;
    renderLayer.srcRect.x = srcRect ? srcRect->x : 0;
    renderLayer.srcRect.y = srcRect ? srcRect->y : 0;
    renderLayer.srcRect.w = srcRect ? srcRect->w : layer->size.w;
    renderLayer.srcRect.h = srcRect ? srcRect->h : layer->size.h;
    renderLayer.dstRect.x = dstRect ? dstRect->x : 0;
    renderLayer.dstRect.y = dstRect ? dstRect->y : 0;
    renderLayer.dstRect.w = dstRect ? dstRect->w : layer->size.w;
    renderLayer.dstRect.h = dstRect ? dstRect->h : layer->size.h;
    renderLayer.layer = layer;
    renderLayers.push_back(renderLayer);
}

void ChompGfxWindow::render()
{

    #ifndef EMSCRIPTEN
    SDL_RenderPresent(renderer);
    ChompGfxColor originalColor;
    SDL_GetRenderDrawColor(renderer, &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    setDrawColor(&originalColor);
    #endif

    int windowPixelWidth,windowPixelHeight;
    SDL_GetWindowSize(window, &windowPixelWidth, &windowPixelHeight); 
    uint16_t windowUnitSize = windowPixelWidth > windowPixelHeight ? windowPixelHeight : windowPixelWidth;
    SDL_SetRenderTarget(renderer, nullptr);
    std::sort(renderLayers.begin(), renderLayers.end());
    for (auto &renderLayer : renderLayers) {

        ChompGfxLayer::drawLayerToRenderTarget(
            renderer,
            renderLayer.layer,
            &renderLayer.srcRect,
            &renderLayer.dstRect,
            windowPixelWidth,
            windowPixelHeight,
            windowUnitSize,
            windowUnitSize
        );

    }
    renderLayers.clear();
}