#ifndef CHOMP_GFX_SPRITE_H
#define CHOMP_GFX_SPRITE_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "layer.h"
#include "../asset/bitmap.h"

struct ChompGfxSpriteAnimationData
{
    std::string name;
    std::vector<uint16_t> frames;
};

class ChompGfxSprite : public ChompGfxLayer
{

public:

    static char SPRITE_ASSET_PREFIX[];

    ChompGfxSprite(SDL_Renderer* _renderer, uint8_t* bitmap, ChompGfxSize* _size) : ChompGfxLayer(_renderer, nullptr, _size)
    {
        setTextures(bitmap);
        getAnimationData(bitmap);
        currentAnimation = nullptr;
    }
    ~ChompGfxSprite();

    bool setFrame(uint16_t frame);

    bool setAnimation(char* name);
    void updateAnimationFrame();

protected:

    std::vector<SDL_Texture*> spriteTextures;
    void setTextures(uint8_t* bitmap);
    void getAnimationData(uint8_t* bitmap);

    std::vector<ChompGfxSpriteAnimationData> animationData;
    ChompGfxSpriteAnimationData* currentAnimation;
    uint8_t animationFramerate;
};

#endif