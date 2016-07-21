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

void ChompGfxLayer::toPixels(ChompGfxSize* _size, uint16_t* width, uint16_t* height)
{
    *width = (uint16_t) abs( _size ? (float) _size->w * (float) pixelUnitWidth : pixelUnitWidth );
    *height = (uint16_t) abs( _size ? (float) _size->h * (float) pixelUnitHeight : pixelUnitHeight );
}

void ChompGfxLayer::toPixels(ChompGfxPosition* _pos, uint16_t* x, uint16_t* y)
{
    *x = (uint16_t) abs( _pos ? (float) _pos->x * (float) pixelUnitWidth : pixelUnitWidth );
    *y = (uint16_t) abs( _pos ? (float) _pos->y * (float) pixelUnitHeight : pixelUnitHeight );
}

ChompGfxSize ChompGfxLayer::getPixelSize(uint16_t width, uint16_t height)
{
    ChompGfxSize _size;
    _size.w = (float) width / (float) pixelUnitWidth;
    _size.h = (float) height / (float) pixelUnitHeight;
    return _size;
}

ChompGfxPosition ChompGfxLayer::getPixelPosition(uint16_t x, uint16_t y)
{
    ChompGfxSize size = getPixelSize(x, y);
    ChompGfxPosition pos;
    pos.x = size.w;
    pos.y = size.h;
    return pos;
}

void ChompGfxLayer::fill()
{
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderFillRect(renderer, nullptr);
}

void ChompGfxLayer::drawLine(ChompGfxPosition* pos1, ChompGfxPosition* pos2)
{
    if (!pos1 || !pos2) {
        return;
    }
    uint16_t x1, y1, x2, y2;
    toPixels(pos1, &x1, &y1);
    toPixels(pos2, &x2, &y2);
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderDrawLine(
        renderer,
        x1,
        y1,
        x2,
        y2
    );
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
        dstLayer->getPixelUnitWidth(),
        dstLayer->getPixelUnitHeight()
    );

}

void ChompGfxLayer::drawLayerToRenderTarget(SDL_Renderer* renderer, ChompGfxLayer* srcLayer, ChompGfxRect* srcRect, ChompGfxRect* dstRect, uint16_t targetUnitWidth, uint16_t targetUnitHeight)
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
    sdlDstRect.w = dstRect ? dstRect->w * targetUnitWidth : targetUnitWidth * srcLayer->size.w;
    sdlDstRect.h = dstRect ? dstRect->h * targetUnitHeight : targetUnitHeight * srcLayer->size.h;

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