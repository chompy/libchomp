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

#include "layer.h"

Chomp::GfxLayer::GfxLayer(SDL_Renderer* _renderer, SDL_Texture* _texture, Chomp::GfxSize* _size)
{
    renderer = _renderer;
    texture = _texture;
    size.w = _size ? _size->w : 1;
    size.h = _size ? _size->h : 1;
    zIndex = 0;
    rotation = 0;
    flip = CHOMP_GFX_FLIP_NONE;
    setPixelSize();
}

Chomp::GfxLayer::~GfxLayer()
{
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Chomp::GfxLayer::toPixels(Chomp::GfxSize* _size, uint16_t* w, uint16_t* h)
{
    *w = (uint16_t) abs( _size ? (float) _size->w * (float) pixelUnitWidth : pixelUnitWidth );
    *h = (uint16_t) abs( _size ? (float) _size->h * (float) pixelUnitHeight : pixelUnitHeight );
}

void Chomp::GfxLayer::toPixels(Chomp::GfxPosition* pos, uint16_t* x, uint16_t* y)
{
    *x = (uint16_t) abs( pos ? (float) pos->x * (float) pixelUnitWidth : pixelUnitWidth );
    *y = (uint16_t) abs( pos ? (float) pos->y * (float) pixelUnitHeight : pixelUnitHeight );
}

void Chomp::GfxLayer::toPixels(Chomp::GfxRect* rect, uint16_t* x, uint16_t* y, uint16_t* w, uint16_t* h)
{
    *x = (uint16_t) abs( rect ? (float) rect->x * (float) pixelUnitWidth : pixelUnitWidth );
    *y = (uint16_t) abs( rect ? (float) rect->y * (float) pixelUnitHeight : pixelUnitHeight );
    *w = (uint16_t) abs( rect ? (float) rect->w * (float) pixelUnitWidth : pixelUnitWidth );
    *h = (uint16_t) abs( rect ? (float) rect->h * (float) pixelUnitHeight : pixelUnitHeight );
}

Chomp::GfxSize Chomp::GfxLayer::getPixelSize(const uint16_t w, const uint16_t h)
{
    Chomp::GfxSize _size;
    _size.w = (float) w / (float) pixelUnitWidth;
    _size.h = (float) h / (float) pixelUnitHeight;
    return _size;
}

Chomp::GfxPosition Chomp::GfxLayer::getPixelPosition(const uint16_t x, const uint16_t y)
{
    Chomp::GfxSize size = getPixelSize(x, y);
    Chomp::GfxPosition pos;
    pos.x = size.w;
    pos.y = size.h;
    return pos;
}

bool Chomp::GfxLayer::hasCollision(Chomp::GfxRect* rect1, Chomp::GfxRect* rect2)
{
    if (!rect1 || !rect2) {
        return false;
    }
    return (rect1->x < (rect2->x + rect2->w) && (rect1->x + rect1->w) > rect2->x &&
    rect1->y < (rect2->y + rect2->h) && (rect1->y + rect1->h) > rect2->y);
}

bool Chomp::GfxLayer::hasCollision(Chomp::GfxPosition* pos1, Chomp::GfxRect* rect2)
{
    if (!pos1 || !rect2) {
        return false;
    }
    Chomp::GfxRect rect1;
    rect1.x = pos1->x;
    rect1.y = pos1->y;
    rect1.w = size.w;
    rect1.h = size.h;
    return hasCollision(
        &rect1,
        rect2
    );
}

bool Chomp::GfxLayer::hasCollision(Chomp::GfxPosition* pos1, Chomp::GfxLayer* layer2, Chomp::GfxPosition* pos2)
{
    if (!pos1 || !layer2 || !pos2) {
        return false;
    }
    Chomp::GfxRect rect1;
    rect1.x = pos1->x;
    rect1.y = pos1->y;
    rect1.w = size.w;
    rect1.w = size.h;
    Chomp::GfxRect rect2;
    rect2.x = pos2->x;
    rect2.y = pos2->y;
    rect2.w = layer2->size.w;
    rect2.w = layer2->size.h;
    return hasCollision(
        &rect1,
        &rect2
    );
}

void Chomp::GfxLayer::fill()
{
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderFillRect(renderer, NULL);
}

void Chomp::GfxLayer::drawLine(Chomp::GfxPosition* pos1, Chomp::GfxPosition* pos2)
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

void Chomp::GfxLayer::drawRect(Chomp::GfxRect* rect)
{
    uint16_t x, y, w, h;
    SDL_Rect sdlRect;
    toPixels(rect, &x, &y, &w, &h);
    sdlRect.x = x;
    sdlRect.y = y;
    sdlRect.w = w;
    sdlRect.h = h;
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderDrawRect(renderer, &sdlRect);
}

void Chomp::GfxLayer::drawFillRect(Chomp::GfxRect* rect)
{
    if (!rect) {
        return fill();
    }
    uint16_t x, y, w, h;
    SDL_Rect sdlRect;
    toPixels(rect, &x, &y, &w, &h);
    sdlRect.x = x;
    sdlRect.y = y;
    sdlRect.w = w;
    sdlRect.h = h;
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderFillRect(renderer, &sdlRect);
}

void Chomp::GfxLayer::drawLayer(Chomp::GfxLayer* layer, Chomp::GfxRect* srcRect, Chomp::GfxRect* dstRect)
{
    return Chomp::GfxLayer::drawLayerToLayer(
        renderer,
        layer,
        this,
        srcRect,
        dstRect
    );
}

void Chomp::GfxLayer::drawLayerToLayer(SDL_Renderer* renderer, Chomp::GfxLayer* srcLayer, Chomp::GfxLayer* dstLayer, Chomp::GfxRect* srcRect, Chomp::GfxRect* dstRect)
{

    if (!renderer || !srcLayer || !dstLayer) {
        return;
    }
    SDL_SetRenderTarget(renderer, dstLayer->texture);
    return Chomp::GfxLayer::drawLayerToRenderTarget(
        renderer,
        srcLayer,
        srcRect,
        dstRect,
        dstLayer->getPixelUnitWidth(),
        dstLayer->getPixelUnitHeight()
    );

}

void Chomp::GfxLayer::drawLayerToRenderTarget(SDL_Renderer* renderer, Chomp::GfxLayer* srcLayer, Chomp::GfxRect* srcRect, Chomp::GfxRect* dstRect, uint16_t targetUnitWidth, uint16_t targetUnitHeight)
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
    sdlDstRect.y = dstRect ? dstRect->y * targetUnitHeight : 0;
    sdlDstRect.w = dstRect ? dstRect->w * targetUnitWidth : targetUnitWidth * srcLayer->size.w;
    sdlDstRect.h = dstRect ? dstRect->h * targetUnitHeight : targetUnitHeight * srcLayer->size.h;

    // if no rotations or flips then use basic render copy for speed
    if (srcLayer->rotation == 0 && srcLayer->flip == CHOMP_GFX_FLIP_NONE) {

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
            case CHOMP_GFX_FLIP_HORIZONTAL:
            {
                flip = SDL_FLIP_HORIZONTAL;
                break;
            }
            case CHOMP_GFX_FLIP_VERTICAL:
            {
                flip = SDL_FLIP_VERTICAL;
                break;
            }
            case CHOMP_GFX_FLIP_BOTH:
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
            NULL,        // @todo implement center point ?
            flip
        );
    }

}

void Chomp::GfxLayer::setPixelSize()
{
    if (texture) {
        int _pixelWidth, _pixelHeight;
        SDL_QueryTexture(
            texture,
            NULL,
            NULL,
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