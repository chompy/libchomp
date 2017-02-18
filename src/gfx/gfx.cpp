#include "gfx.h"

Chomp::Gfx::Gfx()
{

    // init sdl systems
    if (!SDL_WasInit(SDL_INIT_VIDEO) == 0 && SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw Chomp::SdlException();
    }
    
    // init sdl ttf
    #ifndef WITHOUT_SDL_TTF
    if (!TTF_WasInit() && TTF_Init() == -1) {
        throw Chomp::SdlTtfException();
    }
    #endif

    // create window
    window = SDL_CreateWindow(
        "LibChomp Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CHOMP_GFX_DEFAULT_WINDOW_W,
        CHOMP_GFX_DEFAULT_WINDOW_H,
        SDL_WINDOW_SHOWN |
        SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        throw Chomp::SdlException();
        return;
    }

    // create renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        throw Chomp::SdlException();
        return;
    }

    setCameraPosition(NULL);
    setDrawColor(NULL);

}

Chomp::Gfx::~Gfx()
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

Chomp::GfxSize Chomp::Gfx::getWindowSize()
{
    int ww,wh;
    SDL_GetWindowSize(window, &ww, &wh);
    Chomp::GfxSize size;
    if (ww > wh) {
        size.h = 1.0;
        size.w = (float) ww / (float) wh;
    } else {
        size.w = 1.0;
        size.h = (float) wh / (float) ww;
    }
    return size;
}

void Chomp::Gfx::setWindowTitle(const char* title)
{
    SDL_SetWindowTitle(
        window,
        title
    );
}

Chomp::GfxPosition Chomp::Gfx::getCameraPosition()
{
    return camera;
}

void Chomp::Gfx::toPixelSize(Chomp::GfxSize* size, uint16_t* width, uint16_t* height)
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

Chomp::GfxSize Chomp::Gfx::fromPixelSize(const uint16_t width, const uint16_t height)
{
    Chomp::GfxSize size;
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

void Chomp::Gfx::setCameraPosition(Chomp::GfxPosition* position)
{
    camera.x = position ? position->x : 0;
    camera.y = position ? position->y : 0;
}

void Chomp::Gfx::setDrawColor(Chomp::GfxColor* color)
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

void Chomp::Gfx::setCursorVisibility(bool state)
{
    if (state) {
        SDL_ShowCursor(SDL_ENABLE);
        return;
    }
    SDL_ShowCursor(SDL_DISABLE);
}

Chomp::GfxLayer* Chomp::Gfx::newLayer(Chomp::GfxSize* size)
{
    return newLayer(
        size->w * CHOMP_GFX_DEFAULT_LAYER_PIXEL_SIZE,
        size->h * CHOMP_GFX_DEFAULT_LAYER_PIXEL_SIZE,
        size
    );
}

Chomp::GfxLayer* Chomp::Gfx::newLayer(const uint16_t pixelWidth, const uint16_t pixelHeight, Chomp::GfxSize* size)
{
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        pixelWidth,
        pixelHeight
    );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    return new Chomp::GfxLayer(
        renderer,
        texture,
        size
    );
}

Chomp::GfxLayer* Chomp::Gfx::newLayerFromBitmap(uint8_t* bitmap, const uint16_t frame, Chomp::GfxSize* size)
{
    if (!bitmap) {
        return NULL;
    }
    return new Chomp::GfxLayer(
        renderer,
        Chomp::Bitmap::getTexture(renderer, bitmap, frame),
        size
    );
}

Chomp::GfxSprite* Chomp::Gfx::newSprite(const char* spriteName, Chomp::GfxSize* size)
{
    if (!spriteName) {
        return NULL;
    }
    // build asset name string
    std::string assetName = std::string(Chomp::GfxSprite::SPRITE_ASSET_PREFIX) + std::string(spriteName);
    // asset handler
    Chomp::Asset asset;
    // load asset
    if (!asset.assetExists(assetName.c_str())) {
        return NULL;
    }
    // get filesize
    uint32_t fileSize = asset.getAssetSize(assetName.c_str());
    // make bitmap
    std::vector<uint8_t> bitmap(fileSize, 0);
    asset.readFile(assetName.c_str(), 0, &bitmap[0], fileSize);
    // new sprite layer
    return new Chomp::GfxSprite(
        renderer,
        &bitmap[0],
        size
    );
}

Chomp::GfxText* Chomp::Gfx::newTextLayer(const char* fontName, const uint16_t ptSize, Chomp::GfxSize* size)
{
    return newTextLayer(
        fontName,
        ptSize,
        size->w * CHOMP_GFX_DEFAULT_LAYER_PIXEL_SIZE,
        size->h * CHOMP_GFX_DEFAULT_LAYER_PIXEL_SIZE,
        size
    );
}

Chomp::GfxText* Chomp::Gfx::newTextLayer(const char* fontName, const uint16_t ptSize, const uint16_t pixelWidth, const uint16_t pixelHeight, Chomp::GfxSize* size)
{
    if (!fontName) {
        return NULL;
    }
    // build asset name string
    std::string assetName = std::string(Chomp::GfxText::FONT_ASSET_PREFIX) + std::string(fontName);
    // asset handler
    Chomp::Asset asset;
    // get filesize
    uint32_t fileSize = asset.getAssetSize(assetName.c_str());
    // get font data
    std::vector<uint8_t> fontData(fileSize, 0);
    asset.readFile(assetName.c_str(), 0, &fontData[0], fileSize);
    // new texture
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        pixelWidth,
        pixelHeight
    );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    // new text layer
    return new Chomp::GfxText(
        renderer,
        &fontData[0],
        fileSize,
        ptSize,
        texture,
        size
    );
}

void Chomp::Gfx::addLayerToRenderer(Chomp::GfxLayer* layer, Chomp::GfxRect* srcRect, Chomp::GfxRect* dstRect)
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

void Chomp::Gfx::render()
{

    if (!window || !renderer) {
        return;
    }

    SDL_SetRenderTarget(renderer, NULL);

    #ifndef EMSCRIPTEN
    Chomp::GfxColor originalColor;
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
        Chomp::GfxLayer::drawLayerToRenderTarget(
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