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

Chomp::GfxLayer::GfxLayer(SDL_Renderer* _renderer, SDL_Texture* _texture)
{
    renderer = _renderer;
    texture = _texture;
    zIndex = 0;
    rotation = 0;
    flip = CHOMP_GFX_FLIP_NONE;
}

Chomp::GfxLayer::~GfxLayer()
{
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

Chomp::GfxSize Chomp::GfxLayer::getSize()
{
    Chomp::GfxSize _size;
    _size.w = 0;
    _size.h = 0;
    if (!texture) {
        return _size;
    }
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    _size.w = w;
    _size.h = h;
    return _size;
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
    rect1.w = getSize().w;
    rect1.h = getSize().h;
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
    rect1.w = getSize().w;
    rect1.w = getSize().h;
    Chomp::GfxRect rect2;
    rect2.x = pos2->x;
    rect2.y = pos2->y;
    rect2.w = layer2->getSize().w;
    rect2.w = layer2->getSize().h;
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
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderDrawLine(
        renderer,
        pos1->x,
        pos1->y,
        pos2->x,
        pos2->y
    );
}

void Chomp::GfxLayer::drawRect(Chomp::GfxRect* rect)
{
    SDL_Rect sdlRect;
    sdlRect.x = rect ? rect->x : 0;
    sdlRect.y = rect ? rect->y : 0;
    sdlRect.w = rect ? rect->w : getSize().w;
    sdlRect.h = rect ? rect->h : getSize().h;
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderDrawRect(renderer, &sdlRect);
}

void Chomp::GfxLayer::drawFillRect(Chomp::GfxRect* rect)
{
    if (!rect) {
        return fill();
    }
    SDL_Rect sdlRect;
    sdlRect.x = rect->x;
    sdlRect.y = rect->y;
    sdlRect.w = rect->w;
    sdlRect.h = rect->h;
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
        dstRect
    );

}

void Chomp::GfxLayer::drawLayerToRenderTarget(SDL_Renderer* renderer, Chomp::GfxLayer* srcLayer, Chomp::GfxRect* srcRect, Chomp::GfxRect* dstRect)
{

    // must have renderer and source layer
    if (!renderer || !srcLayer) {
        return;
    }

    SDL_Rect sdlSrcRect;
    sdlSrcRect.x = srcRect ? srcRect->x : 0;
    sdlSrcRect.y = srcRect ? srcRect->y : 0;
    sdlSrcRect.w = srcRect ? srcRect->w : srcLayer->getSize().w;
    sdlSrcRect.h = srcRect ? srcRect->h : srcLayer->getSize().h;

    SDL_Rect sdlDstRect;
    sdlDstRect.x = dstRect ? dstRect->x : 0;
    sdlDstRect.y = dstRect ? dstRect->y : 0;
    sdlDstRect.w = dstRect ? dstRect->w : srcLayer->getSize().w;
    sdlDstRect.h = dstRect ? dstRect->h : srcLayer->getSize().h;

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