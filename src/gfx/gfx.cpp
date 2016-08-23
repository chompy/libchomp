#include "gfx.h"

ChompGfx::ChompGfx()
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

ChompGfx::~ChompGfx()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
}

ChompGfxSize ChompGfx::getWindowSize()
{
    ChompGfxSize size;
    return size;
}

ChompGfxPosition ChompGfx::getCameraPosition()
{
    return camera;
}

void ChompGfx::toPixelSize(ChompGfxSize* size, uint16_t* width, uint16_t* height)
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

ChompGfxSize ChompGfx::fromPixelSize(uint16_t width, uint16_t height)
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

void ChompGfx::setCameraPosition(ChompGfxPosition* position)
{
    camera.x = position ? position->x : 0;
    camera.y = position ? position->y : 0;
}

void ChompGfx::setDrawColor(ChompGfxColor* color)
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

ChompGfxLayer* ChompGfx::newLayer(uint16_t pixelWidth, uint16_t pixelHeight, ChompGfxSize* size)
{
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        pixelWidth,
        pixelHeight
    );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    return new ChompGfxLayer(
        renderer,
        texture,
        size
    );
}

ChompGfxLayer* ChompGfx::newLayerFromBitmap(uint8_t* bitmap, uint16_t frame, ChompGfxSize* size)
{
    if (!bitmap) {
        return nullptr;
    }
    return new ChompGfxLayer(
        renderer,
        ChompBitmap::getTexture(renderer, bitmap, frame),
        size
    );
}

ChompGfxSprite* ChompGfx::newSprite(char* spriteName, ChompGfxSize* size)
{
    if (!spriteName) {
        return nullptr;
    }
    // build asset name string
    uint8_t assetPrefixLen = strlen(ChompGfxSprite::SPRITE_ASSET_PREFIX);
    char assetName[assetPrefixLen + strlen(spriteName) + 1];
    memcpy(assetName, ChompGfxSprite::SPRITE_ASSET_PREFIX, assetPrefixLen);
    memcpy(&assetName[assetPrefixLen], spriteName, strlen(spriteName));
    assetName[assetPrefixLen + strlen(spriteName)] = '\0';
    // load asset
    if (!ChompAsset::assetExists(assetName)) {
        return nullptr;
    }
    // get filesize
    uint32_t fileSize = ChompAsset::getAssetSize(assetName);
    // make bitmap
    std::vector<uint8_t> bitmap(fileSize, 0);
    ChompAsset::readFile(assetName, 0, &bitmap[0], fileSize);
    // new sprite layer
    return new ChompGfxSprite(
        renderer,
        &bitmap[0],
        size
    );
}

void ChompGfx::addLayerToRenderer(ChompGfxLayer* layer, ChompGfxRect* srcRect, ChompGfxRect* dstRect)
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

void ChompGfx::render()
{

    if (!window || !renderer) {
        return;
    }

    SDL_SetRenderTarget(renderer, nullptr);

    #ifndef EMSCRIPTEN
    ChompGfxColor originalColor;
    SDL_GetRenderDrawColor(renderer, &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    setDrawColor(&originalColor);
    #endif

    int windowPixelWidth,windowPixelHeight;
    SDL_GetWindowSize(window, &windowPixelWidth, &windowPixelHeight); 
    uint16_t windowUnitSize = windowPixelWidth > windowPixelHeight ? windowPixelHeight : windowPixelWidth;
    std::sort(renderLayers.begin(), renderLayers.end());
    for (auto &renderLayer : renderLayers) {

        ChompGfxLayer::drawLayerToRenderTarget(
            renderer,
            renderLayer.layer,
            &renderLayer.srcRect,
            &renderLayer.dstRect,
            windowUnitSize,
            windowUnitSize
        );

    }
    renderLayers.clear();

    #ifndef EMSCRIPTEN
    SDL_RenderPresent(renderer);
    #endif
}