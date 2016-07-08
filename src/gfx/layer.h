#ifndef CHOMP_GFX_LAYER_H
#define CHOMP_GFX_LAYER_H

#include <SDL2/SDL.h>
#include "structs.h"

class ChompGfxLayer
{
public:

    ChompGfxLayer(SDL_Renderer* _renderer, SDL_Texture* _texture, ChompGfxSize* _size);
    ~ChompGfxLayer();
    bool operator<(const ChompGfxLayer &layer) const { return layer.position.z > position.z; }

    // sdl texture
    SDL_Texture* texture;

    // size / position
    ChompGfxPosition position;
    ChompGfxSize size;    

    // general draw
    void drawLayer(ChompGfxLayer* layer, ChompGfxPosition* position, ChompGfxSize* size);

protected:

    SDL_Renderer* renderer;
    uint16_t pixelWidth, pixelHeight;

};

#endif