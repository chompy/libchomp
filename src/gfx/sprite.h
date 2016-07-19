#ifndef CHOMP_GFX_SPRITE_H
#define CHOMP_GFX_SPRITE_H

#include <SDL2/SDL.h>
#include <vector>
#include "layer.h"
#include "../asset/bitmap.h"

class ChompGfxSprite : public ChompGfxLayer
{

public:

    static char SPRITE_ASSET_PREFIX[];

    ChompGfxSprite(SDL_Renderer* _renderer, uint8_t* bitmap, ChompGfxSize* _size) : ChompGfxLayer(_renderer, nullptr, _size)
    {
        setTextures(bitmap);
    }
    ~ChompGfxSprite();

    bool setFrame(uint16_t frame);

protected:

    std::vector<SDL_Texture*> spriteTextures;
    void setTextures(uint8_t* bitmap);

};

#endif