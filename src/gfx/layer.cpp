#include "layer.h"

ChompGfxLayer::ChompGfxLayer(SDL_Renderer* _renderer, SDL_Texture* _texture, ChompGfxSize* _size)
{
    renderer = _renderer;
    texture = _texture;
    size.w = _size ? _size->w : 1;
    size.h = _size ? _size->h : 1;
    position.x = 0;
    position.y = 0;
    position.z = 0;
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
        pixelUnitWidth = pixelWidth / _size.w;
        pixelUnitHeight = pixelHeight / size.h;
    }
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

void ChompGfxLayer::drawLayer(ChompGfxLayer* layer, ChompGfxPosition* position, ChompGfxSize* size)
{
    
}