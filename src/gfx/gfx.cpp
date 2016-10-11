#include "gfx.h"

ChompGfx::ChompGfx()
{

    // init sdl systems
    if (!SDL_WasInit(SDL_INIT_VIDEO) == 0 && SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw ChompSdlException();
    }
    
    // init sdl ttf
    #ifndef WITHOUT_SDL_TTF
    if (!TTF_WasInit() && TTF_Init() == -1) {
        throw ChompSdlTtfException();
    }
    #endif

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
        throw ChompSdlException();
        return;
    }

    // create renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (!renderer) {
        throw ChompSdlException();
        return;
    }

    setCameraPosition(NULL);
    setDrawColor(NULL);

}

ChompGfx::~ChompGfx()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    #ifndef WITHOUT_SDL_TTF
    if (TTF_WasInit()) {
        TTF_Quit();
    }
    #endif
}

ChompGfxSize ChompGfx::getWindowSize()
{
    int ww,wh;
    SDL_GetWindowSize(window, &ww, &wh);
    ChompGfxSize size;
    if (ww > wh) {
        size.h = 1.0;
        size.w = (float) ww / (float) wh;
    } else {
        size.w = 1.0;
        size.h = (float) wh / (float) ww;
    }
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

ChompGfxSize ChompGfx::fromPixelSize(const uint16_t width, const uint16_t height)
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

ChompGfxLayer* ChompGfx::newLayer(const uint16_t pixelWidth, const uint16_t pixelHeight, ChompGfxSize* size)
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

ChompGfxLayer* ChompGfx::newLayerFromBitmap(uint8_t* bitmap, const uint16_t frame, ChompGfxSize* size)
{
    if (!bitmap) {
        return NULL;
    }
    return new ChompGfxLayer(
        renderer,
        ChompBitmap::getTexture(renderer, bitmap, frame),
        size
    );
}

ChompGfxSprite* ChompGfx::newSprite(const char* spriteName, ChompGfxSize* size)
{
    if (!spriteName) {
        return NULL;
    }
    // build asset name string
    uint8_t assetPrefixLen = strlen(ChompGfxSprite::SPRITE_ASSET_PREFIX);
    char assetName[assetPrefixLen + strlen(spriteName) + 1];
    memcpy(assetName, ChompGfxSprite::SPRITE_ASSET_PREFIX, assetPrefixLen);
    memcpy(&assetName[assetPrefixLen], spriteName, strlen(spriteName));
    assetName[assetPrefixLen + strlen(spriteName)] = '\0';
    // load asset
    if (!ChompAsset::assetExists(assetName)) {
        return NULL;
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

ChompGfxText* ChompGfx::newTextLayer(const char* fontName, uint16_t ptSize, ChompGfxSize* size)
{
    if (!fontName) {
        return NULL;
    }
    // build asset name string
    uint8_t assetPrefixLen = strlen(ChompGfxText::FONT_ASSET_PREFIX);
    char assetName[assetPrefixLen + strlen(fontName) + 1];
    memcpy(assetName, ChompGfxText::FONT_ASSET_PREFIX, assetPrefixLen);
    memcpy(&assetName[assetPrefixLen], fontName, strlen(fontName));
    assetName[assetPrefixLen + strlen(fontName)] = '\0';
    // load asset
    if (!ChompAsset::assetExists(assetName)) {
        return NULL;
    }
    // get filesize
    uint32_t fileSize = ChompAsset::getAssetSize(assetName);
    // get font data
    std::vector<uint8_t> fontData(fileSize, 0);
    ChompAsset::readFile(assetName, 0, &fontData[0], fileSize);
    // new text layer
    return new ChompGfxText(
        renderer,
        &fontData[0],
        fileSize,
        ptSize,
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

    SDL_SetRenderTarget(renderer, NULL);

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

    for (uint16_t i = 0; i < renderLayers.size(); i++) {
        RenderLayers renderLayer = renderLayers[i];
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