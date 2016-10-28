#ifndef CHOMP_GFX_SPRITE_H
#define CHOMP_GFX_SPRITE_H

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

    ChompGfxSprite(SDL_Renderer* _renderer, uint8_t* bitmap, ChompGfxSize* _size) : ChompGfxLayer(_renderer, NULL, _size)
    {
        animationFramerate = 10;
        setTextures(bitmap);
        getAnimationData(bitmap);
        currentAnimation = NULL;
        lastAnimationTick = 0;
        animationIndex = 0;
    }
    ~ChompGfxSprite();

    bool setFrame(const uint16_t frame);

    bool setAnimation(const char* name);
    void updateAnimationFrame();

protected:

    std::vector<SDL_Texture*> spriteTextures;
    void setTextures(uint8_t* bitmap);
    void getAnimationData(uint8_t* bitmap);

    std::vector<ChompGfxSpriteAnimationData> animationData;
    ChompGfxSpriteAnimationData* currentAnimation;
    uint16_t animationFramerate;
    uint32_t lastAnimationTick;
    uint16_t animationIndex;
};

#endif