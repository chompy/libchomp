#include "layer.h"

ChompGfxLayer::ChompGfxLayer(SDL_Renderer* _renderer, SDL_Texture* _texture, ChompGfxSize* _size)
{
    renderer = _renderer;
    texture = _texture;
    size.w = _size ? _size->w : 1;
    size.h = _size ? _size->h : 1;
    zIndex = 0;
    rotation = 0;
    flip = FLIP_NONE;
    setPixelSize();
}

ChompGfxLayer::~ChompGfxLayer()
{
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void ChompGfxLayer::toPixelSize(ChompGfxSize* _size, uint16_t* width, uint16_t* height)
{
    *width = (uint16_t) abs( _size ? _size->w : 1.0 * (float) pixelUnitWidth );
    *height = (uint16_t) abs( _size ? _size->h : 1.0 * (float) pixelUnitHeight );
}

ChompGfxSize ChompGfxLayer::fromPixelSize(uint16_t width, uint16_t height)
{
    ChompGfxSize _size;
    _size.w = (float) width / (float) pixelUnitWidth;
    _size.h = (float) height / (float) pixelUnitHeight;
    return _size;
}

void ChompGfxLayer::drawLayer(ChompGfxLayer* layer, ChompGfxRect* srcRect, ChompGfxRect* dstRect)
{
    return ChompGfxLayer::drawLayerToLayer(
        renderer,
        layer,
        this,
        srcRect,
        dstRect
    );
}

void ChompGfxLayer::drawLayerToLayer(SDL_Renderer* renderer, ChompGfxLayer* srcLayer, ChompGfxLayer* dstLayer, ChompGfxRect* srcRect, ChompGfxRect* dstRect)
{

    if (!renderer || !srcLayer || !dstLayer) {
        return;
    }
    SDL_SetRenderTarget(renderer, dstLayer->texture);
    return ChompGfxLayer::drawLayerToRenderTarget(
        renderer,
        srcLayer,
        srcRect,
        dstRect,
        dstLayer->getPixelWidth(),
        dstLayer->getPixelHeight(),
        dstLayer->getPixelUnitWidth(),
        dstLayer->getPixelUnitHeight()
    );

}

void ChompGfxLayer::drawLayerToRenderTarget(SDL_Renderer* renderer, ChompGfxLayer* srcLayer, ChompGfxRect* srcRect, ChompGfxRect* dstRect, uint16_t targetWidth, uint16_t targetHeight, uint16_t targetUnitWidth, uint16_t targetUnitHeight)
{

    // must have renderer and source layer
    if (!renderer || !srcLayer) {
        return;
    }

    SDL_Rect sdlSrcRect;
    sdlSrcRect.x = srcRect ? srcRect->x * srcLayer->getPixelUnitWidth() : 0;
    sdlSrcRect.y = srcRect ? srcRect->y * srcLayer->getPixelUnitHeight() : 0;
    sdlSrcRect.w = srcRect ? srcRect->w * srcLayer->getPixelUnitWidth() : srcLayer->size.w * srcLayer->getPixelUnitWidth();
    sdlSrcRect.h = srcRect ? srcRect->h * srcLayer->getPixelUnitHeight() : srcLayer->size.h * srcLayer->getPixelUnitHeight();

    SDL_Rect sdlDstRect;
    sdlDstRect.x = dstRect ? dstRect->x * targetUnitWidth : 0;
    sdlDstRect.y = dstRect ? dstRect->x * targetUnitHeight : 0;
    sdlDstRect.w = dstRect ? dstRect->w * targetUnitWidth : targetWidth;
    sdlDstRect.h = dstRect ? dstRect->h * targetUnitHeight : targetHeight;

    // if no rotations or flips then use basic render copy for speed
    if (srcLayer->rotation == 0 && srcLayer->flip == FLIP_NONE) {

        SDL_RenderCopy(
            renderer,
            srcLayer->texture,
            &sdlSrcRect,
            &sdlDstRect
        );

    // otherwise use render copy ex
    } else {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        switch(srcLayer->flip)
        {
            case FLIP_HORIZONTAL:
            {
                flip = SDL_FLIP_HORIZONTAL;
                break;
            }
            case FLIP_VERTICAL:
            {
                flip = SDL_FLIP_VERTICAL;
                break;
            }
            case FLIP_BOTH:
            {
                flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
                break;
            }
        }
        SDL_RenderCopyEx(
            renderer,
            srcLayer->texture,
            &sdlSrcRect,
            &sdlDstRect,
            srcLayer->rotation,
            nullptr,        // @todo implement center point ?
            flip
        );
    }

}

void ChompGfxLayer::setPixelSize()
{
    if (texture) {
        int _pixelWidth, _pixelHeight;
        SDL_QueryTexture(
            texture,
            nullptr,
            nullptr,
            &_pixelWidth,
            &_pixelHeight
        );
        pixelWidth = (uint16_t) _pixelWidth;
        pixelHeight = (uint16_t) _pixelHeight;
        pixelUnitWidth = pixelWidth / size.w;
        pixelUnitHeight = pixelHeight / size.h;
    } else {
        pixelWidth = 1;
        pixelHeight = 1;
        pixelUnitWidth = 1;
        pixelUnitHeight = 1;
    }
}