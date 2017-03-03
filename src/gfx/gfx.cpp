/**
    This file is part of Libchomp.

    Libchomp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Libchomp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Libchomp.  If not, see <http://www.gnu.org/licenses/>.
**/

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
    size.w = ww;
    size.h = wh;
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

Chomp::GfxLayer* Chomp::Gfx::newLayer(Chomp::GfxSize* size)
{
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        size->w,
        size->h
    );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    return new Chomp::GfxLayer(
        renderer,
        texture
    );
}

Chomp::GfxLayer* Chomp::Gfx::newLayerFromBitmap(uint8_t* bitmap, const uint16_t frame)
{
    if (!bitmap) {
        return NULL;
    }
    return new Chomp::GfxLayer(
        renderer,
        Chomp::Bitmap::getTexture(renderer, bitmap, frame)
    );
}

Chomp::GfxSprite* Chomp::Gfx::newSprite(const char* spriteName)
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
    );
}

Chomp::GfxText* Chomp::Gfx::newTextLayer(const char* fontName, const uint16_t ptSize, Chomp::GfxSize* size)
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
    // new text layer
    return new Chomp::GfxText(
        renderer,
        &fontData[0],
        fileSize,
        ptSize,
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
    renderLayer.srcRect.w = srcRect ? srcRect->w : layer->size().w;
    renderLayer.srcRect.h = srcRect ? srcRect->h : layer->size().h;
    renderLayer.dstRect.x = dstRect ? dstRect->x : 0;
    renderLayer.dstRect.y = dstRect ? dstRect->y : 0;
    renderLayer.dstRect.w = dstRect ? dstRect->w : layer->size().w;
    renderLayer.dstRect.h = dstRect ? dstRect->h : layer->size().h;

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

    int windowPixelWidth, windowPixelHeight;
    SDL_GetWindowSize(window, &windowPixelWidth, &windowPixelHeight); 
    std::sort(renderLayers.begin(), renderLayers.end());

    for (uint16_t i = 0; i < renderLayers.size(); i++) {
        RenderLayers renderLayer = renderLayers[i];
        Chomp::GfxLayer::drawLayerToRenderTarget(
            renderer,
            renderLayer.layer,
            &renderLayer.srcRect,
            &renderLayer.dstRect,
        );

    }
    renderLayers.clear();

    #ifndef EMSCRIPTEN
    SDL_RenderPresent(renderer);
    #endif
}